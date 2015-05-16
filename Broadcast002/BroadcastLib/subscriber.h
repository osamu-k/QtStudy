#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QByteArray>

class Subscriber
{
public:
    Subscriber();
    ~Subscriber();
    virtual void deliver(QByteArray data) = 0;
};

#endif // SUBSCRIBER_H
