#ifndef RECTANGLEMAKER_H
#define RECTANGLEMAKER_H

#include "rectangle.h"
#include "shapemaker.h"

class RectangleMaker : public ShapeMaker
{
public:
    RectangleMaker( DrawingSettings *settings );
    ~RectangleMaker();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool readFrom( QDataStream &in, Shape::Type type );

private:
    Rectangle *m_rectangle;
};

#endif // RECTANGLEMAKER_H
