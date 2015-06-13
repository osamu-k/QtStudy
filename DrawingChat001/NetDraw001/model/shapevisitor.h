#ifndef SHAPEVISITOR_H
#define SHAPEVISITOR_H

class FreeHand;
class Rectangle;

class ShapeVisitor
{
public:
    ShapeVisitor();
    virtual ~ShapeVisitor();

    virtual void visit( FreeHand *freeHand ) = 0;
    virtual void visit( Rectangle *rectangle ) = 0;
};

#endif // SHAPEVISITOR_H
