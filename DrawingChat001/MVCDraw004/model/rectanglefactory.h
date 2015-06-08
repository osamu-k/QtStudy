#ifndef RECTANGLEFACTORY_H
#define RECTANGLEFACTORY_H

#include "shapefactory.h"

class RectangleFactory : public ShapeFactory
{
public:
    RectangleFactory();
    ~RectangleFactory();

    Shape *newInstance();
};

#endif // RECTANGLEFACTORY_H
