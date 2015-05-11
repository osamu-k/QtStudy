#include "drawingserver.h"

DrawingServer *DrawingServer::m_instance = 0;

DrawingServer::DrawingServer()
{

}

DrawingServer::~DrawingServer()
{
    clearList();
}

DrawingServer *DrawingServer::instance()
{
    if( m_instance == 0 ){
        m_instance = new DrawingServer;
    }
    return m_instance;
}

void DrawingServer::addShape(Shape *shape)
{
    m_shapeList << shape;
    emit drawingChanged();
//    emit shapeAdded(shape);
}

QList<Shape*> DrawingServer::shapeList()
{
    return m_shapeList;
}

void DrawingServer::clear()
{
    clearList();
    emit drawingChanged();
//    emit cleared();
}

void DrawingServer::clearList()
{
    foreach( Shape *shape, m_shapeList ){
        delete shape;
    }
    m_shapeList.clear();
}
