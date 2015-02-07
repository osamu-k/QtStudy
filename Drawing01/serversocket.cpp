/**
serversocket.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "serversocket.h"

QList<ServerSocket *> ServerSocket::m_instanceList;

ServerSocket *ServerSocket::newInstance(QObject *parent)
{
    ServerSocket *instance = new ServerSocket( parent );
    m_instanceList << instance;
    return instance;
}

ServerSocket::ServerSocket( QObject *parent )
    : ByteArraySocket( parent )
    , m_blockSize( 0 )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(readReceivedData()) );
    connect( this, SIGNAL(disconnected()), this, SLOT(finish()) );
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::broadcastData( QByteArray data )
{
    qDebug() << "Broadcasting data ...";

    foreach( ServerSocket *serverSocket, m_instanceList ){
        serverSocket->send( data );
    }
}

void ServerSocket::finish()
{
    qDebug() << "Disconnected !";
    m_instanceList.removeAll( this );
    deleteLater();
}
