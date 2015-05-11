#include <QDataStream>
#include <QDebug>
#include "broadcasterproxy.h"

BroadcasterProxy::BroadcasterProxy()
{
    connect( &m_socket,&QTcpSocket::connected,this,&BroadcasterProxy::connected);
    connect( &m_socket,&QTcpSocket::disconnected,this,&BroadcasterProxy::disconnected);
    connect( &m_socket,&QTcpSocket::readyRead,this,&BroadcasterProxy::dataReadyRead);

    m_socket.connectToHost("127.0.0.1",12345);
}

BroadcasterProxy::~BroadcasterProxy()
{

}

void BroadcasterProxy::addData(QByteArray data)
{
    QDataStream outStream(&m_socket);
    outStream << data;
    m_socket.flush();
}

void BroadcasterProxy::connected()
{
    qDebug() << "connected";
}

void BroadcasterProxy::disconnected()
{
    qDebug() << "disconnected";
}

void BroadcasterProxy::dataReadyRead()
{
    QDataStream inStream(&m_socket);
    QByteArray data;
    inStream >> data;
    emit newData(data);
}
