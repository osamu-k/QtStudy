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
