#include "rectangle.h"

Rectangle::Rectangle()
    : Shape(TYPE_RECTANGLE)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw( QPainter &painter ) const
{
    painter.setPen(QPen(m_lineColor,m_lineWidth));
    painter.drawRect(
                m_point1.x(),
                m_point1.y(),
                m_point2.x() - m_point1.x(),
                m_point2.y() - m_point1.y() );
}
