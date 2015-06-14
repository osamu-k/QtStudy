#include "rectanglemaker.h"

RectangleMaker::RectangleMaker( DrawingSettings *settings )
    : ShapeMaker( settings )
{
}

RectangleMaker::~RectangleMaker()
{
}

void RectangleMaker::mousePressEvent(QMouseEvent *event)
{
    m_rectangle = new Rectangle();
    m_rectangle->setDrawingSettings(*m_settings);
    m_rectangle->setPoint1(event->pos());
    m_rectangle->setPoint2(event->pos());
}

void RectangleMaker::mouseMoveEvent(QMouseEvent *event)
{
    if( m_rectangle == 0 )
        return;
    m_rectangle->setPoint2(event->pos());
}

void RectangleMaker::mouseReleaseEvent(QMouseEvent *event)
{
    if( m_rectangle == 0 )
        return;
    m_rectangle->setPoint2(event->pos());
    emit newShapeAvailable();
}

void RectangleMaker::draw(QPainter &painter) const
{
    if( m_rectangle ){
        painter.save();
        m_rectangle->draw(painter);
        painter.restore();
    }
}

Shape *RectangleMaker::takeShape()
{
    Shape *shape = m_rectangle;
    m_rectangle = 0;
    return shape;
}
