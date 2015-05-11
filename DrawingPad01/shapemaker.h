#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include <QPainter>
#include <shape.h>

class ShapeMaker
{
public:
    ShapeMaker();
    ~ShapeMaker();
    virtual void begin(QPoint point) = 0;
    virtual void move(QPoint point) = 0;
    virtual Shape *end(QPoint point) = 0;
    virtual void draw(QPainter &painter) = 0;
};

#endif // SHAPEMAKER_H
