#include "shapespace.h"

ShapeSpace::ShapeSpace()
{
}

ShapeSpace::~ShapeSpace()
{
}

ShapeSpace *ShapeSpace::m_instance = 0;

ShapeSpace *ShapeSpace::instance()
{
    if( m_instance == 0 ){
        m_instance = new ShapeSpace();
    }
    return m_instance;
}

void ShapeSpace::addShape( Shape *shape )
{
    m_shapeVector.push_back(shape);
    emit changed();
}

int ShapeSpace::shapeCount() const
{
    return m_shapeVector.size();
}

Shape *ShapeSpace::shape( int index ) const
{
    if( (0 <= index) && (index < m_shapeVector.size()) ){
        return m_shapeVector[index];
    }
    else{
        return 0;
    }
}

void ShapeSpace::clear()
{
    foreach( Shape *shape, m_shapeVector ){
        delete shape;
    }
    m_shapeVector.clear();
    emit changed();
}
