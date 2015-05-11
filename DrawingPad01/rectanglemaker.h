#ifndef RECTANGLEMAKER_H
#define RECTANGLEMAKER_H

#include "rectangle.h"
#include "shapemaker.h"

class RectangleMaker : public ShapeMaker
{
public:
    RectangleMaker();
    ~RectangleMaker();
    void begin(QPoint point);
    void move(QPoint point);
    Shape *end(QPoint point);
    void draw(QPainter &painter);

private:
    Rectangle *m_rectangle;
};

#endif // RECTANGLEMAKER_H
