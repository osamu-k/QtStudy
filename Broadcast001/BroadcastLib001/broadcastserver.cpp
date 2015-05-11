#include <QDataStream>
#include "broadcastserver.h"

BroadcastServer::BroadcastServer()
{
    connect( &m_tcpServer, &QTcpServer::newConnection, this, &BroadcastServer::newConnection );
}

BroadcastServer::~BroadcastServer()
{
//    foreach( QTcpSocket *socket, m_clientSocketList ){
//        delete socket;
//    }
    m_clientSocketList.clear();
}

void BroadcastServer::startListen(int port)
{
    if( m_tcpServer.listen( QHostAddress::Any, port ) ){
        qDebug() << "now listening on port " << port;
    }
    else{
        qDebug() << "listen failed !";
    }
}

void BroadcastServer::newConnection()
{
    while( m_tcpServer.hasPendingConnections() ){
        qDebug() << "New connection !";
        QTcpSocket *socket = m_tcpServer.nextPendingConnection();
        connect( socket, &QTcpSocket::readyRead, this, &BroadcastServer::dataReceived );
        connect( socket, &QTcpSocket::disconnected, this, &BroadcastServer::disconnected );
        m_clientSocketList << socket;
    }
}

void BroadcastServer::dataReceived()
{
    qDebug() << "data recieved !";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if(socket){
        QDataStream inStream(socket);
//        QString data;
        QByteArray data;
        inStream >> data;
        qDebug() << "data.size = " << data.size();
        broadcast(data);
    }
}

void BroadcastServer::disconnected()
{
    qDebug() << "disconnected !";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if(socket){
        m_clientSocketList.removeAll(socket);
        //delete socket;
    }
}

//void BroadcastServer::broadcast(QString data)
//{
//    foreach(QTcpSocket *socket, m_clientSocketList){
//        QDataStream outStream(socket);
//        outStream << data;
//        socket->flush();
//    }
//}

void BroadcastServer::broadcast(QByteArray data)
{
    foreach(QTcpSocket *socket, m_clientSocketList){
        QDataStream outStream(socket);
        outStream << data;
        socket->flush();
    }
}
