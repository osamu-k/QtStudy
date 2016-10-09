#include "chatserver.h"

#include <QDataStream>
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QObject(parent)
{
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

ChatServer::~ChatServer()
{
    for( QTcpSocket *socket: m_socketList ){
        delete m_bufferMap[socket];
        delete socket;
    }
    m_socketList.clear();
    m_bufferMap.clear();
}

void ChatServer::listen(qint16 port)
{
    if (m_tcpServer.listen(QHostAddress::Any,port)){
        qDebug() << "listenning on port " << port;
    }
    else{
        qDebug() << "listen on port " << port << " failed.";
    }
}

void ChatServer::stop()
{
    qDebug() << "stop to listenning.";
    m_tcpServer.close();
}

void ChatServer::newConnection()
{
    while(m_tcpServer.hasPendingConnections()){
        QTcpSocket *socket = m_tcpServer.nextPendingConnection();
        qDebug() << "newConnection accepted."
                 << " peer address: " << socket->peerAddress()
                 << " peer port: " << socket->peerPort();
        m_socketList << socket;
        MessageBuffer *buffer = new MessageBuffer;
        m_bufferMap[socket] = buffer;
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    }
}

void ChatServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    MessageBuffer *buffer = m_bufferMap[socket];

    buffer->readData(socket);
    if( buffer->isComplete() ){
        QString message = buffer->message();
        qDebug() << "received message size: " << message.size();

        for( auto socket : m_socketList ){
            castMessage( socket, message );
        }
    }
}

void ChatServer::castMessage(QTcpSocket *socket, QString message)
{
    QByteArray buffer;
    QDataStream dataStream(&buffer, QIODevice::WriteOnly);
    dataStream << message;

    QDataStream out(socket);
    quint32 size = buffer.size();
    qDebug() << "send data size: " << size;
    out << size;
    socket->write(buffer.constData(),buffer.size());
    socket->flush();
}

void ChatServer::disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if( socket ){
        qDebug() << "disconnected."
                 << " peer address: " << socket->peerAddress()
                 << " peer port: " << socket->peerPort();
    }
    else{
        qDebug() << "disconnected."
                 << " sender(): " << sender();
    }
    m_socketList.removeAll(socket);
    socket->deleteLater();
}
