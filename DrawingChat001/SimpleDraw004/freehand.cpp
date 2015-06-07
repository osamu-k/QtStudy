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
    painter.setPen(QPen(m_lineColor,m_lineWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawPolyline(m_polygon);
    painter.restore();
}
