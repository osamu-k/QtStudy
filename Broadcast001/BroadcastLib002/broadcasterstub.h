#ifndef BROADCASTERSTUB_H
#define BROADCASTERSTUB_H

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include "broadcaster.h"

class BroadcasterStub : public QObject
{
    Q_OBJECT
public:
    BroadcasterStub(Broadcaster *broadcaster,QTcpSocket *socket);
    ~BroadcasterStub();
    void addData(QByteArray data);
private slots:
    void dataReceived();
    void disconnected();
    void newData(QByteArray data);
private:
    Broadcaster *m_broadcaster;
    QTcpSocket *m_socket;
};

#endif // BROADCASTERSTUB_H
