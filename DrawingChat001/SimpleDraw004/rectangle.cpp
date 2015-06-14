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
    painter.save();
    painter.setPen(QPen(m_lineColor,m_lineWidth,Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));
    painter.drawRect( QRect(m_point1,m_point2) );
    painter.restore();
}
