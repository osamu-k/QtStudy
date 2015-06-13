#ifndef FREEHAND_H
#define FREEHAND_H

#include "shape.h"

#include <QColor>
#include <QPolygon>

class FreeHand : public Shape
{
public:
    FreeHand();
    ~FreeHand();

    void addPoint(QPoint point);
    QPoint point(int index) const;

    void accept( ShapeVisitor *visitor ) { visitor->visit(this); }

    void writeTo(QDataStream &out) const;
    void readFrom(QDataStream &in);

    QPolygon polygon() const { return m_polygon; }

private:
    QPolygon m_polygon;
};

#endif // FREEHAND_H
