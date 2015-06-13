#include "shapemaker.h"
#include "netshapespace.h"

ShapeMaker::ShapeMaker( DrawingSettings *settings )
    : m_settings(settings)
{
}

ShapeMaker::~ShapeMaker()
{
}

Shape *ShapeMaker::newShape( Shape::Type type )
{
    Shape *shape = NetShapeSpace::instance()->newShape(type);
    m_view->addWorkingShape( shape );
    return shape;
}

void ShapeMaker::shapeChanged( Shape *shape )
{
    m_view->update();
}

void ShapeMaker::shapeCompleted( Shape *shape )
{
    m_view->removeWorkngShape( shape );
    NetShapeSpace::instance()->addShape(shape);
}

void ShapeMaker::shapeCanceled( Shape *shape )
{
    m_view->removeWorkngShape( shape );
    free( shape );
}
