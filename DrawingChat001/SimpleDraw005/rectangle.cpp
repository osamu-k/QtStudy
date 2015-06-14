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
    QRect rect(m_point1,m_point2);

    if( m_settings.isFillColorEnabled()){
        painter.fillRect(rect,QBrush(m_settings.fillColor()));
    }
    if( m_settings.isOutlineEnabled()){
        painter.setPen(QPen(m_settings.lineColor(),m_settings.lineWidth(),Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));
        painter.drawRect(rect);
    }
    painter.restore();
}
