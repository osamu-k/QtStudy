#include "chatserver.h"

#include <QDataStream>
#include <QDebug>

ChatServer *ChatServer::m_instance = nullptr;

ChatServer *ChatServer::instance(){
    if(m_instance == nullptr){
        m_instance = new ChatServer;
    }
    return m_instance;
}

ChatServer::ChatServer(QObject *parent)
    : QObject(parent)
    , m_tcpServer(nullptr)
{
    m_tcpServer = new QTcpServer(this);
    connect( m_tcpServer, &QTcpServer::acceptError, this, &ChatServer::serverAcceptError);
    connect( m_tcpServer, &QTcpServer::newConnection, this, &ChatServer::serverNewConnection);
}

void ChatServer::listen(const QHostAddress &address, quint16 port)
{
    qDebug() << "listen( " << address << ", " << port << ")";
    m_tcpServer->listen(address, port);
}

void ChatServer::close()
{
    qDebug() << "close";
    m_tcpServer->close();
}

void ChatServer::serverAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "accept error: " + socketError;
}

void ChatServer::serverNewConnection()
{
    qDebug() << "new connection";
    while( m_tcpServer->hasPendingConnections() ){
        QTcpSocket *tcpSocket = m_tcpServer->nextPendingConnection();
        connect(tcpSocket, &QIODevice::readyRead, this, &ChatServer::socketReadyRead);
        connect(tcpSocket,&QAbstractSocket::disconnected, this, &ChatServer::socketDisconnected);
        m_tcpSocketList << tcpSocket;
        emit connected(tcpSocket);
    }
}

void ChatServer::socketReadyRead()
{
    qDebug() << "socket ready read";
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    while(senderSocket->bytesAvailable() > 0){
        QDataStream inStream(senderSocket);
        QString message;
        inStream >> message;
        emit messageReceived(senderSocket, message);
        for( auto socket: m_tcpSocketList ){
            QDataStream outStream(socket);
            outStream << message;
            socket->flush();
        }
    }
}

void ChatServer::socketDisconnected()
{
    qDebug() << "socket disconnected";
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    m_tcpSocketList.removeAll(senderSocket);
    emit disconnected(senderSocket);
}
