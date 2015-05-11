#include <QDataStream>
#include "broadcasterstub.h"

BroadcasterStub::BroadcasterStub(Broadcaster *broadcaster, QTcpSocket *socket)
    : m_broadcaster(broadcaster), m_socket(socket)
{
    connect(m_socket,&QTcpSocket::readyRead,this,&BroadcasterStub::dataReceived);
    connect(m_socket,&QTcpSocket::disconnected, this, &BroadcasterStub::disconnected );
    connect(m_broadcaster,&Broadcaster::newData,this,&BroadcasterStub::newData);
}

BroadcasterStub::~BroadcasterStub()
{
}

void BroadcasterStub::addData(QByteArray data)
{
    m_broadcaster->addData(data);
}

void BroadcasterStub::dataReceived()
{
    QDataStream inStream(m_socket);
    QByteArray data;
    inStream >> data;
    m_broadcaster->addData(data);
}

void BroadcasterStub::disconnected()
{
    deleteLater();
}

void BroadcasterStub::newData(QByteArray data)
{
    QDataStream outStream(m_socket);
    outStream << data;
    m_socket->flush();
}
