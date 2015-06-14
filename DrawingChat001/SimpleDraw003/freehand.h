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

    void draw( QPainter &painter ) const;

private:
    QPolygon m_polygon;
};

#endif // FREEHAND_H
