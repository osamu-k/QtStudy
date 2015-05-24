#ifndef FREEHANDPAINTER_H
#define FREEHANDPAINTER_H

#include <QPainter>
#include "freehand.h"

class FreeHandPainter
{
public:
    FreeHandPainter();
    ~FreeHandPainter();
    void draw(QPainter &painter, FreeHand *shape);
};

#endif // FREEHANDPAINTER_H
