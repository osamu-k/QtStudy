#include "chatclient.h"

#include <QDataStream>
#include <QDebug>

ChatClient *ChatClient::m_instance = nullptr;

ChatClient *ChatClient::instance(){
    if(m_instance == nullptr){
        m_instance = new ChatClient;
    }
    return m_instance;
}

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_tcpSocket(nullptr)
{
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::connected, this, &ChatClient::socketConnected);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &ChatClient::socketDisconnected);
    connect<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(
                m_tcpSocket, &QAbstractSocket::error, this, &ChatClient::socketError);
    connect(m_tcpSocket, &QIODevice::readyRead, this, &ChatClient::socketReadyRead);
}

void ChatClient::connectToHost(const QString &hostName, quint16 port)
{
    qDebug() << "connect to host( " + hostName + ", " + port + ")";
    m_tcpSocket->connectToHost(hostName, port);
}

void ChatClient::disconnectFromHost()
{
    qDebug() << "disconnect from host.";
    m_tcpSocket->disconnectFromHost();
}

void ChatClient::send(QString message)
{
    qDebug() <<"send message: " + message;
    QDataStream outStream(m_tcpSocket);
    outStream << message;
    m_tcpSocket->flush();
}

void ChatClient::socketConnected()
{
    qDebug() << "socket connected.";
}

void ChatClient::socketDisconnected()
{
    qDebug() << "socket disconnected.";
}

void ChatClient::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "socket error: " << socketError;
}

void ChatClient::socketReadyRead()
{
    qDebug() << "socket ready read.";
    qDebug() << "available bytes: " << m_tcpSocket->bytesAvailable();

    while(m_tcpSocket->bytesAvailable()){
        QDataStream inStream(m_tcpSocket);
        QString message;
        inStream >> message;
        emit received(message);
    }
}
