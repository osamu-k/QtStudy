#ifndef FREEHANDMAKER_H
#define FREEHANDMAKER_H

#include "freehand.h"
#include "shapemaker.h"

class FreeHandMaker : public ShapeMaker
{
public:
    FreeHandMaker( DrawingSettings *settings );
    ~FreeHandMaker();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    Shape *takeShape();

    bool readFrom( QDataStream &in, Shape::Type type );

private:
    FreeHand *m_freeHand;
};

#endif // FREEHANDMAKER_H
