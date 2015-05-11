#include "broadcastclient.h"

BroadcastClient::BroadcastClient()
{
    connect(&m_socket,&QTcpSocket::connected,this,&BroadcastClient::connected);
    connect(&m_socket,&QTcpSocket::readyRead,this,&BroadcastClient::dataReceivedFromHost);
}

BroadcastClient::~BroadcastClient()
{

}

void BroadcastClient::connectToHost()
{
    m_socket.connectToHost("127.0.0.1", 12345);
}

void BroadcastClient::connected()
{
    qDebug() << "connected !";
}

void BroadcastClient::disconnectFromHost()
{
    qDebug() << "disconnect ...";
    m_socket.disconnectFromHost();
}

void BroadcastClient::sendData(QByteArray data)
{
    qDebug() << "send data.";

    QDataStream outStream(&m_socket);
    outStream << data;
    m_socket.flush();
}

void BroadcastClient::dataReceivedFromHost()
{
    qDebug() << "data recieved !";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if(socket){
        QDataStream inStream(socket);
        QByteArray data;
        inStream >> data;
        qDebug() << "data.size = " << data.size();
        emit dataReceived(data);
    }
}
