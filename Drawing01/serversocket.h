/**
serversocket.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QList>
#include <QTcpSocket>

#include "bytearraysocket.h"

class ServerSocket : public ByteArraySocket
{
    Q_OBJECT

public:
    ServerSocket( QObject *parent = 0 );
    ~ServerSocket();

    static ServerSocket *newInstance( QObject *parent = 0 );

private slots:
    void broadcastData( QByteArray );
    void finish();

private:
    static QList<ServerSocket *> m_instanceList;
    qint16 m_blockSize;
};

#endif // SERVERSOCKET_H
