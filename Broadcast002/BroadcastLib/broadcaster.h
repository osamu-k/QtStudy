#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QByteArray>

class Subscriber;

class Broadcaster
{
public:
    static Broadcaster *instance();

    virtual void subscribe(Subscriber *subscriber) = 0;
    virtual void unsubscribe(Subscriber *subscriber) = 0;
    virtual void post(QByteArray data) = 0;

protected:
    Broadcaster();
    virtual ~Broadcaster();
};

#endif // BROADCASTER_H
