#ifndef BROADCASTERSERVER_H
#define BROADCASTERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "broadcaster.h"
#include "broadcasterstub.h"

class BroadcasterServer : public QObject
{
    Q_OBJECT
public:
    BroadcasterServer(Broadcaster *broadcaster);
    ~BroadcasterServer();
    void startListen(int port);
private slots:
    void newConnection();
private:
    Broadcaster *m_broadcaster;
    QTcpServer m_tcpServer;
};

#endif // BROADCASTERSERVER_H
