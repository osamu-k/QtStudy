#include <QDebug>

#include "drawingmodel.h"
#include "freehand.h"
#include "rectangle.h"
#include "shapetypes.h"

DrawingModel::DrawingModel()
{
    connect(&m_broadcastClient,&BroadcastClient::dataReceived,this,&DrawingModel::dataReceived);
}

DrawingModel::~DrawingModel()
{
    clearList();
}

void DrawingModel::addShape(Shape *shape)
{
    m_shapeList << shape;

    QByteArray byteArray;
    QDataStream outStream(&byteArray,QIODevice::WriteOnly);
    shape->writeTo(outStream);
    m_broadcastClient.sendData(byteArray);
//    notify();
    emit drawingChanged();
}

QList<Shape *> DrawingModel::shapeList()
{
    return m_shapeList;
}

void DrawingModel::clear()
{
    clearList();
    emit drawingChanged();
}

void DrawingModel::writeTo( QDataStream &outStream )
{
    outStream << m_shapeList.size();
    foreach( Shape *shape, m_shapeList ){
        shape->writeTo(outStream);
    }
}

void DrawingModel::readFrom( QDataStream &inStream )
{
    qDebug() << "Reading ...";
    int size;
    inStream >> size;
    qDebug() << "  size=" << size;
    for(int i = 0; i < size; i++){
        Shape *shape = readShape(inStream);
        if(shape){
            addShape(shape);
        }
    }
}

Shape *DrawingModel::readShape(QDataStream &inStream)
{
    int type;
    inStream >> type;
    qDebug() << "  type=" << type;
    Shape *shape = 0;
    switch(type){
    case SHAPE_TYPE_FREEHAND:
    {
        shape = new FreeHand;
        shape->readFrom(inStream);
        break;
    }
    case SHAPE_TYPE_RECTANGLE:
    {
        shape = new Rectangle;
        shape->readFrom(inStream);
        break;
    }
    default:
        break;
    }
    return shape;
}

void DrawingModel::clearList()
{
    foreach( Shape *shape, m_shapeList ){
        delete shape;
    }
    m_shapeList.clear();
}

//void DrawingModel::addObserver(DrawingModelObserver *observer)
//{
//    m_observerList << observer;
//}

//void DrawingModel::removeObserver(DrawingModelObserver *observer)
//{
//    m_observerList.removeAll( observer );
//}

//void DrawingModel::notify()
//{
//    foreach( DrawingModelObserver *observer, m_observerList ){
//        observer->notifyDrawingChanged();
//    }
//}

void DrawingModel::connectToHost()
{
    m_broadcastClient.connectToHost();
}

void DrawingModel::disconnectFromtHost()
{
    m_broadcastClient.disconnectFromHost();
}

void DrawingModel::dataReceived(QByteArray data)
{
    QDataStream inStream(data);
    Shape *shape = readShape(inStream);
    if( shape ){
        m_shapeList << shape;
        emit drawingChanged();
    }
}
