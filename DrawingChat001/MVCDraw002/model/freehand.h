#ifndef FREEHAND_H
#define FREEHAND_H

#include "shape.h"

#include <QColor>
#include <QPainter>
#include <QPolygon>

class FreeHand : public Shape
{
public:
    FreeHand();
    ~FreeHand();

    void addPoint(QPoint point);
    QPoint point(int index) const;

    void draw( QPainter &painter ) const;

    void writeTo(QDataStream &out) const;
    void readFrom(QDataStream &in);

private:
    QPolygon m_polygon;
};

#endif // FREEHAND_H
