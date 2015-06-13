#include <QDataStream>
#include "broadcasterimpl.h"
#include "broadcasterstub.h"

BroadcasterStub::BroadcasterStub(QTcpSocket *socket)
    :m_tcpSocket(socket)
{
    m_broadcaster = BroadcasterImpl::instance();
    connect(m_tcpSocket,&QTcpSocket::readyRead, this, &BroadcasterStub::readyRead);
}

BroadcasterStub::~BroadcasterStub()
{

}

void BroadcasterStub::readyRead()
{
    QDataStream inStream(m_tcpSocket);
    QString method;
    inStream >> method;
    if( method == "subscribe" ){
        m_broadcaster->subscribe(this);
    }
    else if( method == "unsubscribe" ){
        m_broadcaster->unsubscribe(this);
    }
    else if( method == "post" ){
        QByteArray data;
        inStream >> data;
        BroadcasterImpl *broadcaster = BroadcasterImpl::instance();
        broadcaster->post(data);
    }
}

void BroadcasterStub::deliver(QByteArray data)
{
    QDataStream outStream(m_tcpSocket);
    outStream << data;
    m_tcpSocket->flush();
}
