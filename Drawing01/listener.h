/**
listener.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QTcpServer>

class ServerSocket;

class Listener : public QTcpServer
{
    Q_OBJECT
public:
    Listener();
    ~Listener();

    void startListen( int port );
    void stopListen();

signals:
    void newConnection( ServerSocket * );

protected:
    void incomingConnection( qintptr );
};

#endif // LISTENER_H
