#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QDataStream>

#include "shape.h"

class ShapeFactory
{
public:
    ShapeFactory();
    virtual ~ShapeFactory();

    virtual Shape *newInstance() = 0;
};

#endif // SHAPEFACTORY_H
