#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include "shapevisitor.h"

#include <QPainter>

class DrawVisitor : public ShapeVisitor
{
public:
    DrawVisitor( QPainter &painter );
    ~DrawVisitor();

    void visit( FreeHand *freeHand );
    void visit( Rectangle *rectangle );

private:
    QPainter &m_painter;
};

#endif // DRAWVISITOR_H
