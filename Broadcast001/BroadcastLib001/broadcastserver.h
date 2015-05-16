#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "bytearraytransmitter.h"

class BroadcastServer : public QObject
{
    Q_OBJECT

public:
    BroadcastServer();
    ~BroadcastServer();
    void startListen(int port);

private slots:
    void newConnection();
//    void dataReceived();
//    void broadcast(QString data);
    void broadcast(QByteArray data);
    void disconnected();

private:
    QTcpServer m_tcpServer;
//    QList<QTcpSocket *> m_clientSocketList;
    QList<ByteArrayTransmitter *> m_clientList;
};

#endif // BROADCASTSERVER_H
