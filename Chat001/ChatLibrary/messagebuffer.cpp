#include "messagebuffer.h"

#include <QDataStream>
#include <QDebug>

MessageBuffer::MessageBuffer()
    : m_size(0)
    , m_receivedSize(0)
{

}

bool MessageBuffer::isEmpty() const
{
    return m_size == 0;
}

void MessageBuffer::setSize(quint32 size)
{
    m_size = size;
    m_receivedSize = 0;
    m_buffer.resize(size);
}

void MessageBuffer::readData(QIODevice *inDevice)
{
    if( isComplete() ){
        clear();
    }
    if( isEmpty() ){
        QDataStream in(inDevice);
        quint32 size;
        in >> size;
        setSize(size);
        qDebug() << "message size received: " << size;
    }
    int readSize = inDevice->read(m_buffer.data() + m_receivedSize, m_size - m_receivedSize);
    m_receivedSize += readSize;
}

bool MessageBuffer::isComplete() const
{
    return m_size == m_receivedSize;
}

QString MessageBuffer::message() const
{
    QDataStream dataStream(m_buffer);
    QString message;
    dataStream >> message;
    return message;
}

void MessageBuffer::clear()
{
    m_size = 0;
    m_receivedSize = 0;
    m_buffer.resize(0);
}
