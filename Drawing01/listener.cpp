/**
listener.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include <QDebug>

#include "listener.h"
#include "serversocket.h"

Listener::Listener()
{

}

Listener::~Listener()
{
}

void Listener::startListen( int port )
{
    if( listen( QHostAddress::Any, port ) ){
        qDebug() << "now listening on port " << port;
    }
    else{
        qDebug() << "listen failed !";
    }
}

void Listener::stopListen()
{
    if( this->isListening() ){
        this->close();
    }
}

void Listener::incomingConnection( qintptr socketDescriptor )
{
    qDebug() << "incomingConnection detected !";
    ServerSocket *serverSocket = ServerSocket::newInstance();
    serverSocket->setSocketDescriptor( socketDescriptor );
    emit newConnection( serverSocket );
}
