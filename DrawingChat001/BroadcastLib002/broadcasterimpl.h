#ifndef BROADCASTERIMPL_H
#define BROADCASTERIMPL_H

#include <QList>
#include "broadcaster.h"

class BroadcasterImpl : public Broadcaster
{
public:
    static BroadcasterImpl *instance();

    void subscribe(Subscriber *subscriber);
    void unsubscribe(Subscriber *subscriber);
    void post(QByteArray data);

private:
    BroadcasterImpl();
    ~BroadcasterImpl();

private:
    static BroadcasterImpl *m_instance;
    QList<Subscriber *> m_subscriberList;
    QList<QByteArray> m_dataList;
};

#endif // BROADCASTERIMPL_H
