#ifndef RECTANGLEPAINTER_H
#define RECTANGLEPAINTER_H

#include <QPainter>
#include "rectangle.h"

class RectanglePainter
{
public:
    RectanglePainter();
    ~RectanglePainter();
    void draw(QPainter &painter, Rectangle *shape);
};

#endif // RECTANGLEPAINTER_H
