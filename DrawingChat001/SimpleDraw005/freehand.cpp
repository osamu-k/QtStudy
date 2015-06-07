#include "freehand.h"

FreeHand::FreeHand()
    : Shape(TYPE_FREEHAND)
{
}

FreeHand::~FreeHand()
{
}

void FreeHand::addPoint(QPoint point)
{
    m_polygon.push_back(point);
}

QPoint FreeHand::point(int index) const
{
    if( (0 <= index) && (index < m_polygon.size()) ){
        return m_polygon.at(index);
    }
    else{
        return QPoint();
    }
}

void FreeHand::draw( QPainter &painter ) const
{
    painter.save();
    painter.setPen(QPen(m_settings.lineColor(),m_settings.lineWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if( m_settings.isFillColorEnabled()){
        painter.setBrush(QBrush(m_settings.fillColor()));
        if( ! m_settings.isOutlineEnabled() ){
            painter.setPen(Qt::NoPen);
        }
        painter.drawPolygon(m_polygon);
    }
    else if( m_settings.isOutlineEnabled() ){
        painter.drawPolyline(m_polygon);
    }
    painter.restore();
}
