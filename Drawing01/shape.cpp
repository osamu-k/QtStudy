/**
shape.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "shape.h"

Shape::Shape()
    : m_lineColor( Qt::black )
    , m_fillColor( Qt::lightGray )
    , m_lineWidth( 1 )
{
}

Shape::~Shape()
{
}

void Shape::setLineColor( QColor color )
{
    m_lineColor = color;
}

QColor Shape::lineColor()
{
    return m_lineColor;
}

void Shape::setLineWidth( int width )
{
    m_lineWidth = width;
}

int Shape::lineWidth()
{
    return m_lineWidth;
}

void Shape::draw(QPainter &)
{
}
