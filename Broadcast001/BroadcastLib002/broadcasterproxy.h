#ifndef BROADCASTERPROXY_H
#define BROADCASTERPROXY_H

#include <QTcpSocket>
#include "broadcaster.h"

class BroadcasterProxy : public Broadcaster
{
    Q_OBJECT
public:
    BroadcasterProxy();
    ~BroadcasterProxy();
    void addData(QByteArray data);
private slots:
    void connected();
    void disconnected();
    void dataReadyRead();
private:
    QTcpSocket m_socket;
};

#endif // BROADCASTERPROXY_H
