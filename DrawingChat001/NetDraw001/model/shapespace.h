#ifndef SHAPESPACE_H
#define SHAPESPACE_H

#include "freehand.h"
#include "rectangle.h"
#include "shape.h"
#include "shapefactory.h"

//#include "broadcaster.h"
//#include "broadcasterproxy.h"
//#include "broadcastserver.h"
//#include "broadcasterimpl.h"
//#include "subscriber.h"

#include <QDataStream>
#include <QMap>
#include <QObject>
#include <QVector>

class ShapeSpace : public QObject
//        , public Subscriber
{
    Q_OBJECT

protected:
    ShapeSpace();
    virtual ~ShapeSpace();

public:
    static ShapeSpace *instance();

    virtual Shape *newShape( Shape::Type type );
    virtual void addShape( Shape *shape );

    int shapeCount() const;
    Shape *shape( int index ) const;
    void clear();

    void writeTo( QDataStream &out ) const;
    void readFrom( QDataStream &in );

signals:
    void changed();

private:
    static ShapeSpace *m_instance;
    QVector<Shape *> m_shapeVector;

    QMap<Shape::Type, ShapeFactory *> m_factoryMap;

//public:
//    enum NetStatus {
//        NET_STATUS_IDLE,
//        NET_STATUS_LISTENING,
//        NET_STATUS_CONNECTING,
//        NET_STATUS_CONNECTED,
//        NET_STATUS_DISCONNECTED
//    };

//public slots:
//    void startListen();
//    void stopListen();
//    void connectToHost();
//    void disconnectFromHost();

//signals:
//    void netStatusChanged(NetStatus);

//private:
//    void deliver(QByteArray data);
//    BroadcastServer m_server;
//    BroadcasterImpl *m_broadcasterImpl;
//    BroadcasterProxy *m_broadcasterProxy;
//    Broadcaster *m_broadcaster;
//    NetStatus m_netStatus;
};

#endif // SHAPESPACE_H
