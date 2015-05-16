#ifndef BROADCASTCLIENT_H
#define BROADCASTCLIENT_H

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include "bytearraytransmitter.h"

class BroadcastClient : public QObject
{
    Q_OBJECT

public:
    BroadcastClient();
    ~BroadcastClient();
    void connectToHost();
    void disconnectFromHost();
    void sendData(QByteArray data);

signals:
    void dataReceived(QByteArray data);

private slots:
//    void connected();
//    void dataReceivedFromHost();

private:
    QTcpSocket m_socket;
    ByteArrayTransmitter m_transmitter;
};

#endif // BROADCASTCLIENT_H
