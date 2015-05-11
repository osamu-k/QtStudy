#include "shape.h"

Shape::Shape(int type)
    : m_type(type)
    , m_color(Qt::black)
    , m_width(0)
{

}

Shape::~Shape()
{

}

int Shape::type()
{
    return m_type;
}

void Shape::setColor(QColor color)
{
    m_color = color;
}

void Shape::setWidth(int width)
{
    m_width = width;
}

QColor Shape::color()
{
    return m_color;
}

int Shape::width()
{
    return m_width;
}

void Shape::writeTo( QDataStream &outStream )
{
    outStream << m_type;
    outStream << m_color;
    outStream << m_width;
}

void Shape::readFrom( QDataStream &inStream )
{
    inStream >> m_color;
    inStream >> m_width;
}
