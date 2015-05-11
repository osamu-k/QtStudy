#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class BroadcastServer : public QObject
{
    Q_OBJECT

public:
    BroadcastServer();
    ~BroadcastServer();
    void startListen(int port);

private slots:
    void newConnection();
    void dataReceived();
    void disconnected();

private:
//    void broadcast(QString data);
    void broadcast(QByteArray data);
    QTcpServer m_tcpServer;
    QList<QTcpSocket *> m_clientSocketList;
};

#endif // BROADCASTSERVER_H
