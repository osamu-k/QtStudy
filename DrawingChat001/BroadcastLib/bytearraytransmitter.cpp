#include "bytearraytransmitter.h"

ByteArrayTransmitter::ByteArrayTransmitter(QTcpSocket *socket)
    : m_socket( socket )
    , m_blockSize( 0 )
{
    connect( m_socket, &QTcpSocket::readyRead, this, &ByteArrayTransmitter::readReceivedData );
    connect( m_socket, &QTcpSocket::disconnected, this, &ByteArrayTransmitter::disconnected );
}

ByteArrayTransmitter::~ByteArrayTransmitter()
{

}

void ByteArrayTransmitter::send(QByteArray data)
{
    qDebug() << "Sending data. isOpen() = " << m_socket->isOpen();
    if( m_socket->isOpen() ){
        QDataStream out( m_socket );
        out << qint32( data.size() );
        out.writeRawData( data.constData(), data.size() );
        m_socket->flush();
    }
}

void ByteArrayTransmitter::readReceivedData()
{
    qDebug() << "reading data..." << m_socket->bytesAvailable() << "bytes available.";

    QDataStream in( m_socket );
    in.setVersion( QDataStream::Qt_5_4 );

    while( m_socket->bytesAvailable() ){
        if( m_blockSize == 0 ){
            if( m_socket->bytesAvailable() < (qint64)sizeof( quint32 ) ){
                return;
            }
            in >> m_blockSize;
            qDebug() << "Block size = " << m_blockSize;
        }
        if( m_socket->bytesAvailable() < m_blockSize ){
            return;
        }
        qDebug() << "Data has read !";
        QByteArray byteArray( m_blockSize, 0 );
        in.readRawData( byteArray.data(), m_blockSize );
        emit received( byteArray );

        m_blockSize = 0;
    }
}
