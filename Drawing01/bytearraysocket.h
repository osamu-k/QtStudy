/**
bytearraysocket.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef BYTEARRAYSOCKET_H
#define BYTEARRAYSOCKET_H

#include <QByteArray>
#include <QTcpSocket>

class ByteArraySocket : public QTcpSocket
{
    Q_OBJECT

public:
    ByteArraySocket( QObject *parent = 0 );
    ~ByteArraySocket();

signals:
    void received( QByteArray );

public slots:
    void send( QByteArray );
    void readReceivedData();

private:
    qint16 m_blockSize;
};

#endif // BYTEARRAYSOCKET_H
