#ifndef BROADCASTER
#define BROADCASTER

#include <QByteArray>
#include <QObject>

class Broadcaster : public QObject
{
    Q_OBJECT
public:
    Broadcaster(){}
    virtual ~Broadcaster(){}
    virtual void addData(QByteArray data) = 0;
signals:
    void newData(QByteArray data);
};

#endif // BROADCASTER
