#ifndef NETSHAPESPACE_H
#define NETSHAPESPACE_H

#include <QObject>
#include "shapespace.h"
#include "broadcaster.h"
#include "broadcasterproxy.h"
#include "broadcastserver.h"
#include "broadcasterimpl.h"
#include "subscriber.h"

class NetShapeSpace : public ShapeSpace
                    , public Subscriber
{
    Q_OBJECT

protected:
    static NetShapeSpace *m_instance;
    NetShapeSpace();
    ~NetShapeSpace();
public:
    static NetShapeSpace *instance();

public:
    virtual void addShape( Shape *shape );

public:
    enum NetStatus {
        NET_STATUS_IDLE,
        NET_STATUS_LISTENING,
        NET_STATUS_CONNECTING,
        NET_STATUS_CONNECTED,
        NET_STATUS_DISCONNECTED
    };

public slots:
    void startListen();
    void stopListen();
    void connectToHost();
    void disconnectFromHost();

signals:
    void netStatusChanged(NetStatus);

private:
    void deliver(QByteArray data);
    BroadcastServer m_server;
    Broadcaster *m_broadcaster;
    NetStatus m_netStatus;
};

#endif // NETSHAPESPACE_H
