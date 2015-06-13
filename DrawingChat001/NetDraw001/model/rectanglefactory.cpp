#include "rectanglefactory.h"

#include "rectangle.h"

RectangleFactory::RectangleFactory()
{
}

RectangleFactory::~RectangleFactory()
{
}

Shape *RectangleFactory::newInstance()
{
    return new Rectangle();
}
