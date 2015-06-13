#include "netshapespace.h"

NetShapeSpace::NetShapeSpace()
    : m_broadcaster(0)
    , m_netStatus(NET_STATUS_IDLE)
{
}

NetShapeSpace::~NetShapeSpace()
{
}

NetShapeSpace *NetShapeSpace::m_instance = 0;

NetShapeSpace *NetShapeSpace::instance()
{
    if( m_instance == 0 ){
        m_instance = new NetShapeSpace();
    }
    return m_instance;
}

void NetShapeSpace::addShape( Shape *shape )
{
    if( m_broadcaster == 0 ){
        ShapeSpace::addShape(shape);
    }
    else {
        QByteArray byteArray;
        QDataStream outStream(&byteArray,QIODevice::WriteOnly);
        outStream << QString("new");
        outStream << static_cast<qint16>(shape->type());
        shape->writeTo(outStream);
        m_broadcaster->post(byteArray);
    }
}

void NetShapeSpace::startListen()
{
    if( m_netStatus == NET_STATUS_IDLE ){
        if( m_server.listen() ){
            m_netStatus = NET_STATUS_LISTENING;
            m_broadcaster = BroadcasterImpl::instance();
            m_broadcaster->subscribe(this);
            emit netStatusChanged(m_netStatus);
        }
    }
}

void NetShapeSpace::stopListen()
{
    if( m_netStatus == NET_STATUS_LISTENING ){
        m_server.close();
        m_netStatus = NET_STATUS_IDLE;
        m_broadcaster->unsubscribe(this);
        m_broadcaster = 0;
        emit netStatusChanged(m_netStatus);
    }
}

void NetShapeSpace::connectToHost()
{
    if( m_netStatus == NET_STATUS_IDLE ){
        m_netStatus = NET_STATUS_CONNECTED;
        m_broadcaster = Broadcaster::instance();
        m_broadcaster->subscribe(this);
        emit netStatusChanged(m_netStatus);
    }
}

void NetShapeSpace::disconnectFromHost()
{
    if( m_netStatus == NET_STATUS_CONNECTED ){
        m_netStatus = NET_STATUS_IDLE;
        m_broadcaster = Broadcaster::instance();
        m_broadcaster->unsubscribe(this);
        m_broadcaster = 0;
        emit netStatusChanged(m_netStatus);
    }
}

void NetShapeSpace::deliver(QByteArray data)
{
    QDataStream inStream(data);
    QString command;
    inStream >> command;
    if( command == "new" ){
        qint16 i16;
        inStream >> i16;
        Shape::Type type = static_cast<Shape::Type>(i16);
//        if( m_factoryMap.contains(type) ){
//            Shape *shape = m_factoryMap[type]->newInstance();
            Shape *shape = newShape(type);
            if( shape ){
                shape->readFrom(inStream);
//                m_shapeVector.push_back(shape);
//                emit changed();
                ShapeSpace::addShape(shape);
            }
//        }
    }
}
