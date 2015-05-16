#include "broadcasterimpl.h"
#include "subscriber.h"

BroadcasterImpl *BroadcasterImpl::m_instance = 0;

//Broadcaster *Broadcaster::instance()
//{
//    return BroadcasterImpl::instance();
//}

BroadcasterImpl *BroadcasterImpl::instance()
{
    if(m_instance == 0){
        m_instance = new BroadcasterImpl();
    }
    return m_instance;
}

BroadcasterImpl::BroadcasterImpl()
{
}

BroadcasterImpl::~BroadcasterImpl()
{
}

void BroadcasterImpl::subscribe(Subscriber *subscriber)
{
    m_subscriberList << subscriber;
//    foreach(QByteArray data, m_dataList){
//        subscriber->deliver(data);
//    }
}

void BroadcasterImpl::unsubscribe(Subscriber *subscriber)
{
    m_subscriberList.removeAll(subscriber);
}

void BroadcasterImpl::post(QByteArray data)
{
    m_dataList << data;
    foreach(Subscriber *subscriber, m_subscriberList){
        subscriber->deliver(data);
    }
}
