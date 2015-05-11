#include "rectanglemaker.h"
#include "shapepainter.h"

RectangleMaker::RectangleMaker()
    : m_rectangle(0)
{

}

RectangleMaker::~RectangleMaker()
{

}

void RectangleMaker::begin(QPoint point)
{
    m_rectangle = new Rectangle;
    m_rectangle->setColor(Qt::red);
    m_rectangle->setFillColor(Qt::yellow);
    m_rectangle->setWidth(5);
    m_rectangle->setPoint1(point);
    m_rectangle->setPoint2(point);
}

void RectangleMaker::move(QPoint point)
{
    if( m_rectangle ){
        m_rectangle->setPoint2(point);
    }
}

Shape *RectangleMaker::end(QPoint point)
{
    Shape *shape = 0;
    if( m_rectangle ){
        m_rectangle->setPoint2(point);
        m_rectangle->setColor(Qt::blue);
        m_rectangle->setFillColor((Qt::green));
        m_rectangle->setWidth(10);
        shape = m_rectangle;
        m_rectangle = 0;
    }
    return shape;
}

void RectangleMaker::draw(QPainter &painter)
{
    ShapePainter shapePainter(painter);
    if( m_rectangle ){
        painter.save();
        painter.setOpacity(0.5);
//        m_rectangle->draw(painter);
        m_rectangle->handle(&shapePainter);
        painter.restore();
    }
}
