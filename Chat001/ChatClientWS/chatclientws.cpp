#include "chatclientws.h"

//#include <QDataStream>

#include <QDebug>

ChatClientWS::ChatClientWS(QObject *parent)
    : QObject(parent)
    , m_state(UnconnectedState)
{
    connect(&m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(&m_socket, SIGNAL(textMessageReceived(const QString &)),
            this, SLOT(textMessageReceived(const QString &)));
    connect(&m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
}

void ChatClientWS::connectToServer(QString server, qint16 port)
{
    QString urlString( QString("ws://%1:%2/").arg(server).arg(port));
    qDebug() << "connecting to server: " << urlString;
    m_socket.open(QUrl(urlString));
}

void ChatClientWS::disconnectFromServer()
{
    qDebug() << "disconnecting from server.";
    m_socket.close();
}

void ChatClientWS::post(QString message)
{
    qDebug() << "posting message: " << message;
    m_socket.sendTextMessage( message );

//    QByteArray buffer;
//    QDataStream dataStream(&buffer, QIODevice::WriteOnly);
//    dataStream << message;

//    QDataStream out(&m_tcpSocket);
//    quint32 size = buffer.size();
//    qDebug() << "send data size: " << size;
//    out << size;
//    m_tcpSocket.write(buffer.constData(),buffer.size());

//    m_tcpSocket.flush();
}

void ChatClientWS::connected()
{
    qDebug() << "connected.";
}

void ChatClientWS::disconnected()
{
    qDebug() << "disconnected.";
}

void ChatClientWS::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error: " << socketError << " : " << m_socket.errorString();
    emit error(m_socket.errorString());
}

void ChatClientWS::textMessageReceived(const QString &message)
{
    emit posted(message);
//    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
//    m_buffer.readData(senderSocket);

//    if( m_buffer.isComplete() ){
//        QString message = m_buffer.message();
//        qDebug() << "message size: " << message.size();
////        qDebug() << "message: " << message;
//        emit posted(message);
//    }
}

void ChatClientWS::socketStateChanged(QAbstractSocket::SocketState socketState)
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

void ChatClientWS::setState(State state)
{
    if( m_state != state ){
        m_state = state;
        emit stateChanged(m_state);
    }
}
