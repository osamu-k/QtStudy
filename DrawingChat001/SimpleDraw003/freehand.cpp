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

void FreeHand::draw( QPainter &painter ) const
{
    painter.save();
    painter.setPen(QPen(m_lineColor,m_lineWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawPolyline(m_polygon);
    painter.restore();
}
