#ifndef FREEHANDFACTORY_H
#define FREEHANDFACTORY_H

#include "shapefactory.h"

class FreeHandFactory : public ShapeFactory
{
public:
    FreeHandFactory();
    ~FreeHandFactory();

    Shape *newInstance();
};

#endif // FREEHANDFACTORY_H
