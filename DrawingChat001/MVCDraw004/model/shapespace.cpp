#include "shapespace.h"

#include "freehandfactory.h"
#include "rectanglefactory.h"

ShapeSpace::ShapeSpace()
{
    m_factoryMap[Shape::TYPE_FREEHAND] = new FreeHandFactory();
    m_factoryMap[Shape::TYPE_RECTANGLE] = new RectangleFactory();
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

Shape *ShapeSpace::newShape( Shape::Type type )
{
    Shape *shape = 0;
    if( m_factoryMap.contains(type) ){
        shape = m_factoryMap[type]->newInstance();
    }
    addShape( shape );
    return shape;

}

void ShapeSpace::addShape( Shape *shape )
{
    m_shapeVector.push_back(shape);
    connect( shape, SIGNAL(changed()), this, SIGNAL(changed()) );
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

void ShapeSpace::writeTo( QDataStream &out ) const
{
    out << static_cast<qint16>(shapeCount());
    for( int i = 0; i < shapeCount(); i++ ){
        Shape *shape = this->shape(i);
        out << static_cast<qint16>(shape->type());
        shape->writeTo( out );
    }
}

void ShapeSpace::readFrom( QDataStream &in )
{
    clear();
    qint16 count;
    in >> count;
    for( int i = 0; i < count; i++ ){
        qint16 i16;
        in >> i16;
        Shape::Type type = static_cast<Shape::Type>(i16);
        if( m_factoryMap.contains(type) ){
            Shape *shape = m_factoryMap[type]->newInstance();
            shape->readFrom(in);
            addShape(shape);
        }
    }
}
