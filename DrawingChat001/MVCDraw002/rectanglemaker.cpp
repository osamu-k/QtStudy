#include "rectanglemaker.h"
#include "shapespace.h"

RectangleMaker::RectangleMaker( DrawingSettings *settings )
    : ShapeMaker( settings )
{
}

RectangleMaker::~RectangleMaker()
{
}

void RectangleMaker::mousePressEvent(QMouseEvent *event)
{
    ShapeSpace *space = ShapeSpace::instance();
    m_rectangle = dynamic_cast<Rectangle *>( space->newShape(Shape::TYPE_RECTANGLE) );
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

bool RectangleMaker::readFrom( QDataStream &in, Shape::Type type )
{
    if( type!= Shape::TYPE_RECTANGLE )
        return false;
    m_rectangle = new Rectangle();
    m_rectangle->readFrom(in);
    return true;
}
