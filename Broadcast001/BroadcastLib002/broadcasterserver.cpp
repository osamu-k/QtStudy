#include "broadcasterserver.h"
#include "broadcasterstub.h"

BroadcasterServer::BroadcasterServer(Broadcaster *broadcaster)
    : m_broadcaster(broadcaster)
{
    connect( &m_tcpServer, &QTcpServer::newConnection, this, &BroadcasterServer::newConnection );
}

BroadcasterServer::~BroadcasterServer()
{

}

void BroadcasterServer::startListen(int port)
{
    if( m_tcpServer.listen( QHostAddress::Any, port ) ){
        qDebug() << "now listening on port " << port;
    }
    else{
        qDebug() << "listen failed !";
    }
}

void BroadcasterServer::newConnection()
{
    while( m_tcpServer.hasPendingConnections() ){
        qDebug() << "New connection !";
        QTcpSocket *socket = m_tcpServer.nextPendingConnection();
        new BroadcasterStub(m_broadcaster,socket);
    }
}

