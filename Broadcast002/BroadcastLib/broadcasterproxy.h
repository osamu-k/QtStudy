#ifndef BROADCASTERPROXY_H
#define BROADCASTERPROXY_H

#include <QObject>
#include <QTcpSocket>
#include "broadcaster.h"
#include "subscriber.h"

class BroadcasterProxy : public QObject, public Broadcaster
{
    Q_OBJECT

public:
    static BroadcasterProxy *instance();

    void subscribe(Subscriber *subscriber);
    void unsubscribe(Subscriber *subscriber);
    void post(QByteArray data);
private:
    BroadcasterProxy();
    ~BroadcasterProxy();
private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void readyRead();
private:
    void sendCommand(QString command);
    static BroadcasterProxy *m_instance;
    QTcpSocket m_tcpSocket;
    Subscriber *m_subscriber;
};

#endif // BROADCASTERPROXY_H
