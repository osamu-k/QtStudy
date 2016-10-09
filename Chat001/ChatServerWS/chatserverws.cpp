#include "chatserverws.h"

ChatServerWS::ChatServerWS(QObject *parent)
    : QObject(parent)
    , m_server("Chat001",QWebSocketServer::NonSecureMode)
{
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void ChatServerWS::listen(qint16 port)
{
    if (m_server.listen(QHostAddress::Any,port)){
        qDebug() << "listenning on port " << port;
    }
    else{
        qDebug() << "listen on port " << port << " failed.";
    }
}

void ChatServerWS::stop()
{
    qDebug() << "stop to listenning.";
    m_server.close();
}

void ChatServerWS::newConnection()
{
    while(m_server.hasPendingConnections()){
        QWebSocket *socket = m_server.nextPendingConnection();
        qDebug() << "newConnection accepted."
                 << " peer address: " << socket->peerAddress()
                 << " peer port: " << socket->peerPort();
        m_socketList << socket;
        MessageBuffer *buffer = new MessageBuffer;
        m_bufferMap[socket] = buffer;
        connect(socket,SIGNAL(textMessageReceived(const QString &)),
                this,SLOT(textMessageReceived(const QString &)));
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    }
}

void ChatServerWS::textMessageReceived(const QString &message)
{

    for( auto socket : m_socketList ){
        socket->sendTextMessage( message );
    }
}

void ChatServerWS::disconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    if( socket ){
        qDebug() << "disconnected."
                 << " peer address: " << socket->peerAddress()
                 << " peer port: " << socket->peerPort();
    }
    else{
        qDebug() << "disconnected."
                 << " sender(): " << sender();
    }
    m_socketList.removeAll(socket);
    socket->deleteLater();
}


