#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QThread>

#define LOG_METHOD_CALLED \
    qDebug() << __PRETTY_FUNCTION__ << " called. " << QThread::currentThread();

#endif // COMMON_H
