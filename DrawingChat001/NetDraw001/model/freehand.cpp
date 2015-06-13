#include "freehand.h"

FreeHand::FreeHand()
    : Shape(TYPE_FREEHAND)
{
}

FreeHand::~FreeHand()
{
}

void FreeHand::addPoint(QPoint point)
{
    m_polygon.push_back(point);
}

QPoint FreeHand::point(int index) const
{
    if( (0 <= index) && (index < m_polygon.size()) ){
        return m_polygon.at(index);
    }
    else{
        return QPoint();
    }
}

void FreeHand::writeTo(QDataStream &out) const
{
    Shape::writeTo(out);
    out << m_polygon;
}

void FreeHand::readFrom(QDataStream &in)
{
    m_polygon.clear();
    Shape::readFrom(in);
    in >> m_polygon;
}
