#include "rectanglepainter.h"

RectanglePainter::RectanglePainter()
{

}

RectanglePainter::~RectanglePainter()
{

}

void RectanglePainter::draw(QPainter &painter, Rectangle *shape)
{
    painter.save();
    QPen pen(shape->color());
    pen.setWidth(shape->width());
//    pen.setCapStyle( Qt::RoundCap );
    painter.setPen(pen);
    QBrush brush(shape->fillColor());
    painter.setBrush(brush);
    painter.drawRect(QRect(shape->point1(),shape->point2()));
    painter.restore();
}
