#ifndef RECTANGLEMAKER_H
#define RECTANGLEMAKER_H

#include "rectangle.h"
#include "shapemaker.h"

class RectangleMaker : public ShapeMaker
{
public:
    RectangleMaker();
    ~RectangleMaker();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void draw(QPainter &painter) const;

    Shape *takeShape();

private:
    Rectangle *m_rectangle;
};

#endif // RECTANGLEMAKER_H
