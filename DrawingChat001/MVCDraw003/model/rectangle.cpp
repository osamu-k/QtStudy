#include "rectangle.h"

Rectangle::Rectangle()
    : Shape(TYPE_RECTANGLE)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::setPoint1(QPoint point)
{
    m_point1 = point;
    emit changed();
}

void Rectangle::setPoint2(QPoint point)
{
    m_point2 = point;
    emit changed();
}

void Rectangle::writeTo(QDataStream &out) const
{
    Shape::writeTo(out);
    out << m_point1;
    out << m_point2;
}

void Rectangle::readFrom(QDataStream &in)
{
    Shape::readFrom(in);
    in >> m_point1;
    in >> m_point2;
}
