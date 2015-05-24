#ifndef SHAPEPAINTER_H
#define SHAPEPAINTER_H

#include <QPainter>
#include "shapehandler.h"

class ShapePainter : public ShapeHandler
{
public:
    ShapePainter(QPainter &painter);
    ~ShapePainter();
    void handleShape( FreeHand * );
    void handleShape( Rectangle * );
    void handleShape( Image * );

private:
    QPainter &m_painter;
};

#endif // SHAPEPAINTER_H
