#include "freehandfactory.h"

#include "freehand.h"

FreeHandFactory::FreeHandFactory()
{
}

FreeHandFactory::~FreeHandFactory()
{
}

Shape *FreeHandFactory::newInstance()
{
    return new FreeHand();
}
