#include <QDataStream>
#include <QDebug>
#include "broadcasterproxy.h"

BroadcasterProxy *BroadcasterProxy::m_instance = 0;

Broadcaster *Broadcaster::instance()
{
    return BroadcasterProxy::instance();
}

BroadcasterProxy *BroadcasterProxy::instance()
{
    if( m_instance == 0 ){
        m_instance = new BroadcasterProxy;
    }
    return m_instance;
}

BroadcasterProxy::BroadcasterProxy()
{
    connect(&m_tcpSocket,&QTcpSocket::connected,this,&BroadcasterProxy::connected);
    connect(&m_tcpSocket,(void (QAbstractSocket::*)(QAbstractSocket::SocketError))&QTcpSocket::error,
                          this,&BroadcasterProxy::error);
    connect(&m_tcpSocket,&QTcpSocket::readyRead,this,&BroadcasterProxy::readyRead);

    qDebug() << "connecting";
    m_tcpSocket.connectToHost("127.0.0.1",12345);
}

BroadcasterProxy::~BroadcasterProxy()
{

}

void BroadcasterProxy::connected()
{
    qDebug() << "connected !";
    if( m_subscriber ){
        sendCommand("subscribe");
    }
}

void BroadcasterProxy::disconnected()
{
    qDebug() << "disconnected !";
}

void BroadcasterProxy::error(QAbstractSocket::SocketError socketError)

{
    qDebug() << "error !";
}

void BroadcasterProxy::readyRead()
{
    QDataStream inStream(&m_tcpSocket);
    QByteArray data;
    inStream >> data;
    m_subscriber->deliver(data);
}

void BroadcasterProxy::subscribe(Subscriber *subscriber)
{
    m_subscriber = subscriber;
    if(m_tcpSocket.state() == QAbstractSocket::ConnectedState ){
        sendCommand("subscribe");
    }
//    QString command("subscribe");
//    QDataStream outStream(&m_tcpSocket);
//    outStream << command;
//    m_tcpSocket.flush();
}

void BroadcasterProxy::unsubscribe(Subscriber *subscriber)
{
    sendCommand("unsubscribe");
    m_subscriber = 0;
//    QString command("unsubscribe");
//    QDataStream outStream(&m_tcpSocket);
//    outStream << command;
//    m_tcpSocket.flush();
}

void BroadcasterProxy::post(QByteArray data)
{
    QString command("post");
    QDataStream outStream(&m_tcpSocket);
    outStream << command;
    outStream << data;
    m_tcpSocket.flush();
}

void BroadcasterProxy::sendCommand(QString command)
{
    QDataStream outStream(&m_tcpSocket);
    outStream << command;
    m_tcpSocket.flush();
}
