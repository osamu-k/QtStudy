#include "shape.h"

Shape::Shape( Type type )
    : m_type(type)
{
}

Shape::~Shape()
{
}

void Shape::writeTo(QDataStream &out) const
{
    m_settings.writeTo(out);
}

void Shape::readFrom(QDataStream &in)
{
    m_settings.readFrom(in);
}
