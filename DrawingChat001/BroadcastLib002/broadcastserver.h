#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "broadcasterimpl.h"

class BroadcastServer : public QObject
{
    Q_OBJECT

public:
    BroadcastServer();
    ~BroadcastServer();

    bool listen();
    void close();

private slots:
    void newConnection();

private:
    BroadcasterImpl *m_broadcaster;
    QTcpServer m_tcpServer;
};

#endif // BROADCASTSERVER_H
