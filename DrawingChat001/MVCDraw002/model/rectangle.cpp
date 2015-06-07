#include "rectangle.h"

Rectangle::Rectangle()
    : Shape(TYPE_RECTANGLE)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::setPoint1(QPoint point)
{
    m_point1 = point;
    emit changed();
}

void Rectangle::setPoint2(QPoint point)
{
    m_point2 = point;
    emit changed();
}

void Rectangle::draw( QPainter &painter ) const
{
    painter.save();
    QRect rect(m_point1.x(),
               m_point1.y(),
               m_point2.x() - m_point1.x(),
               m_point2.y() - m_point1.y() );

    if( m_settings.isFillColorEnabled()){
        painter.fillRect(rect,QBrush(m_settings.fillColor()));
    }
    if( m_settings.isOutlineEnabled()){
        painter.setPen(QPen(m_settings.lineColor(),m_settings.lineWidth()));
        painter.drawRect(rect);
    }
    painter.restore();
}

void Rectangle::writeTo(QDataStream &out) const
{
    Shape::writeTo(out);
    out << m_point1;
    out << m_point2;
}

void Rectangle::readFrom(QDataStream &in)
{
    Shape::readFrom(in);
    in >> m_point1;
    in >> m_point2;
}
