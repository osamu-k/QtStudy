#include <QDebug>
#include "broadcastserver.h"
#include "broadcasterstub.h"

BroadcastServer::BroadcastServer()
{
    m_broadcaster = BroadcasterImpl::instance();
    connect( &m_tcpServer, &QTcpServer::newConnection, this, &BroadcastServer::newConnection );
}

BroadcastServer::~BroadcastServer()
{

}

void BroadcastServer::listen()
{
    qDebug() << "BreadcastServer start listnening.";
    if( m_tcpServer.listen(QHostAddress::Any,12345) ){
        qDebug() << "succeeded !";
    }
    else{
        qDebug() << "failed !";
    }
}

void BroadcastServer::newConnection()
{
    while( m_tcpServer.hasPendingConnections() ){
        QTcpSocket *socket = m_tcpServer.nextPendingConnection();
        BroadcasterStub *stub = new BroadcasterStub(socket);
    }
}

