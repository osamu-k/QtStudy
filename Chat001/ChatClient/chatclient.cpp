#include "chatclient.h"

#include <QDataStream>

#include <QDebug>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_state(UnconnectedState)
{
    connect(&m_tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(&m_tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(&m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&m_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
}

void ChatClient::connectToServer(QString server, qint16 port)
{
    qDebug() << "connecting to server: " << QString("%1:%2").arg(server).arg(port) << ".";
    m_tcpSocket.connectToHost(server,port);
}

void ChatClient::disconnectFromServer()
{
    qDebug() << "disconnecting from server.";
    m_tcpSocket.disconnectFromHost();
}

void ChatClient::post(QString message)
{
    qDebug() << "posting message: " << message;

    QByteArray buffer;
    QDataStream dataStream(&buffer, QIODevice::WriteOnly);
    dataStream << message;

    QDataStream out(&m_tcpSocket);
    quint32 size = buffer.size();
    qDebug() << "send data size: " << size;
    out << size;
    m_tcpSocket.write(buffer.constData(),buffer.size());
    m_tcpSocket.flush();
}

void ChatClient::connected()
{
    qDebug() << "connected.";
}

void ChatClient::disconnected()
{
    qDebug() << "disconnected.";
}

void ChatClient::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error: " << socketError << " : " << m_tcpSocket.errorString();
    emit error(m_tcpSocket.errorString());
}

void ChatClient::readyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    m_buffer.readData(senderSocket);

    if( m_buffer.isComplete() ){
        QString message = m_buffer.message();
        qDebug() << "message size: " << message.size();
//        qDebug() << "message: " << message;
        emit posted(message);
    }

//    QDataStream in(&m_tcpSocket);
//    QString message;
//    in >> message;
//    qDebug() << "message received: " << message;
//    emit posted(message);
}

void ChatClient::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "socket state changed: " << socketState;

    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        setState(UnconnectedState);
        break;
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
        setState(ConnectingState);
        break;
    case QAbstractSocket::ConnectedState:
        setState(ConnectedState);
        break;
    case QAbstractSocket::ClosingState:
        setState(DisconnectingState);
    default:
        break;
    }
}

void ChatClient::setState(State state)
{
    if( m_state != state ){
        m_state = state;
        emit stateChanged(m_state);
    }
}
