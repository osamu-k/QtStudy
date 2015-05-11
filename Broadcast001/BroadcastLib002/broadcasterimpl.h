#ifndef BROADCASTERIMPL_H
#define BROADCASTERIMPL_H

#include <QList>
#include "broadcaster.h"

class BroadcasterImpl : public Broadcaster
{
public:
    BroadcasterImpl();
    ~BroadcasterImpl();
    void addData(QByteArray data);
private:
    QList<QByteArray> m_dataList;
};

#endif // BROADCASTERIMPL_H
