#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

#include <QPoint>

class Rectangle : public Shape
{
public:
    Rectangle();
    ~Rectangle();

    void setPoint1(QPoint point);
    QPoint point1() const { return m_point1; }
    void setPoint2(QPoint point);
    QPoint point2() const { return m_point2; }

    void draw( QPainter &painter ) const;

    void writeTo(QDataStream &out) const;
    void readFrom(QDataStream &in);

private:
    QPoint m_point1;
    QPoint m_point2;
};

#endif // RECTANGLE_H
