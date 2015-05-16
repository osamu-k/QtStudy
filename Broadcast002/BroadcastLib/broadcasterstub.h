#ifndef BROADCASTERSTUB_H
#define BROADCASTERSTUB_H

#include <QObject>
#include <QTcpSocket>
#include "broadcasterimpl.h"
#include "subscriber.h"

class BroadcasterStub : public QObject,  public Subscriber
{
    Q_OBJECT

public:
    BroadcasterStub(QTcpSocket *socket);
    ~BroadcasterStub();

    void deliver(QByteArray data);

private slots:
    void readyRead();

private:
    BroadcasterImpl *m_broadcaster;
    QTcpSocket *m_tcpSocket;
};

#endif // BROADCASTERSTUB_H
