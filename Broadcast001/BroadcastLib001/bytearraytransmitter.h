#ifndef BYTEARRAYTRANSMITTER_H
#define BYTEARRAYTRANSMITTER_H

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>

class ByteArrayTransmitter : public QObject
{
    Q_OBJECT

public:
    ByteArrayTransmitter(QTcpSocket *socket);
    ~ByteArrayTransmitter();

signals:
    void received(QByteArray data);
    void disconnected();

public slots:
    void send(QByteArray data);
    void readReceivedData();

private:
    QTcpSocket *m_socket;
    qint32 m_blockSize;
};

#endif // BYTEARRAYTRANSMITTER_H
