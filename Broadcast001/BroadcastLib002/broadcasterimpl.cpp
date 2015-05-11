#include "broadcasterimpl.h"

BroadcasterImpl::BroadcasterImpl()
{

}

BroadcasterImpl::~BroadcasterImpl()
{

}

void BroadcasterImpl::addData(QByteArray data)
{
    m_dataList << data;
    emit newData(data);
}
