/**
bytearraysocket.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include <QDebug>
#include "bytearraysocket.h"

ByteArraySocket::ByteArraySocket( QObject *parent )
    : QTcpSocket( parent )
    , m_blockSize( 0 )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(readReceivedData()) );
}

ByteArraySocket::~ByteArraySocket()
{
}

void ByteArraySocket::send(QByteArray data)
{
    qDebug() << "Sending data. isOpen() = " << isOpen();
    if( isOpen() ){
        QDataStream out( this );
        out << qint16( data.size() );
        out.writeRawData( data.constData(), data.size() );
        flush();
    }
}

void ByteArraySocket::readReceivedData()
{
    qDebug() << "reading data..." << bytesAvailable() << "bytes available.";

    QDataStream in( this );
    in.setVersion( QDataStream::Qt_5_4 );

    while( bytesAvailable() ){
        if( m_blockSize == 0 ){
            if( bytesAvailable() < (qint64)sizeof( quint16 ) ){
                return;
            }
            in >> m_blockSize;
            qDebug() << "Block size = " << m_blockSize;
        }
        if( bytesAvailable() < m_blockSize ){
            return;
        }
        qDebug() << "Data has read !";
        QByteArray byteArray( m_blockSize, 0 );
        in.readRawData( byteArray.data(), m_blockSize );
        emit received( byteArray );

        m_blockSize = 0;
    }
}

