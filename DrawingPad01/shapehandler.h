#ifndef SHAPEHANDLER_H
#define SHAPEHANDLER_H

class Shape;
class FreeHand;
class Rectangle;
class Image;

class ShapeHandler
{
public:
    ShapeHandler();
    ~ShapeHandler();

    virtual void handleShape( FreeHand * ) = 0;
    virtual void handleShape( Rectangle * ) = 0;
    virtual void handleShape( Image * ) = 0;
};

#endif // SHAPEHANDLER_H
