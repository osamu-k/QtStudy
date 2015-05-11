#ifndef FREEHANDMAKER_H
#define FREEHANDMAKER_H

#include "freehand.h"
#include "shapemaker.h"

class FreeHandMaker : public ShapeMaker
{
public:
    FreeHandMaker();
    ~FreeHandMaker();
    void begin(QPoint point);
    void move(QPoint point);
    Shape *end(QPoint point);
    void draw(QPainter &painter);

private:
    FreeHand *m_freeHand;
};

#endif // FREEHANDMAKER_H
