#ifndef RECTANGLE_H
#define RECTANGLE_H

//#include <QPainter>
#include <QColor>
#include <QPoint>
#include "shape.h"
#include "shapehandler.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    ~Rectangle();
    void setPoint1(QPoint point);
    QPoint point1();
    void setPoint2(QPoint point);
    QPoint point2();
    void setFillColor(QColor color);
    QColor fillColor();
//    void draw(QPainter &painter);
    QRect boundingRect();
    void shift(QPoint diff);
    void writeTo( QDataStream &outStream );
    void readFrom( QDataStream &inStream );
    void handle(ShapeHandler *handler);

private:
    QPoint m_point1;
    QPoint m_point2;
    QColor m_fillColor;
};

#endif // RECTANGLE_H
