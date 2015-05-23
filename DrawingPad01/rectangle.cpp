#include "rectangle.h"
#include "shapetypes.h"
#include <algorithm>

Rectangle::Rectangle()
    : Shape(SHAPE_TYPE_RECTANGLE)
{

}

Rectangle::~Rectangle()
{

}

void Rectangle::setPoint1(QPoint point)
{
    m_point1 = point;
}

QPoint Rectangle::point1()
{
    return m_point1;
}

void Rectangle::setPoint2(QPoint point)
{
    m_point2 = point;
}

QPoint Rectangle::point2()
{
    return m_point2;
}

void Rectangle::setFillColor(QColor color)
{
    m_fillColor = color;
}

QColor Rectangle::fillColor()
{
    return m_fillColor;
}

//void Rectangle::draw( QPainter &painter )
//{
//    painter.save();
//    QPen pen(m_color);
//    pen.setWidth(m_width);
////    pen.setCapStyle( Qt::RoundCap );
//    painter.setPen(pen);
//    QBrush brush(m_fillColor);
//    painter.setBrush(brush);
//    painter.drawRect(QRect(m_point1,m_point2));
//    painter.restore();
//}

QRect Rectangle::boundingRect()
{
    int x1,y1,x2,y2;
    if( m_point1.x() < m_point2.x() ){
        x1 = m_point1.x();
        x2 = m_point2.x();
    }
    else{
        x1 = m_point2.x();
        x2 = m_point1.x();
    }
    if( m_point1.y() < m_point2.y() ){
        y1 = m_point1.y();
        y2 = m_point2.y();
    }
    else{
        y1 = m_point2.y();
        y2 = m_point1.y();
    }
    return QRect(x1,y1,(x2-x1),(y2-y1));
}

void Rectangle::shift(QPoint diff)
{
    m_point1 += diff;
    m_point2 += diff;
}

void Rectangle::handle(ShapeHandler *handler)
{
    handler->handleShape(this);
}

void Rectangle::writeTo( QDataStream &outStream )
{
    Shape::writeTo(outStream);
    outStream << m_fillColor;
    outStream << m_point1;
    outStream << m_point2;
}

void Rectangle::readFrom( QDataStream &inStream )
{
    Shape::readFrom(inStream);
    inStream >> m_fillColor;
    inStream >> m_point1;
    inStream >> m_point2;
}
