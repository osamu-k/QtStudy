#include "freehandpainter.h"

FreeHandPainter::FreeHandPainter()
{

}

FreeHandPainter::~FreeHandPainter()
{

}

void FreeHandPainter::draw(QPainter &painter, FreeHand *shape)
{
    painter.save();
    QPen pen(shape->color());
    pen.setWidth(shape->width());
    pen.setCapStyle( Qt::RoundCap );
    painter.setPen(pen);

    QVector<QPoint> points = shape->points();
    for( int i = 1; i < points.size(); i++ ){
        painter.drawLine(points[i-1],points[i]);
    }
    painter.restore();
}
