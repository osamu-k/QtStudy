#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include <QIODevice>

class MessageBuffer{
public:
    MessageBuffer();
    void readData(QIODevice *inDevice);
    bool isComplete() const;
    QString message() const;

private:
    bool isEmpty() const;
    void setSize(quint32 size);
    void clear();

    quint32 m_size;
    quint32 m_receivedSize;
    QByteArray m_buffer;
};

#endif // MESSAGEBUFFER_H
