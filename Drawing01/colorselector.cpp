/**
colorselector.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "colorselector.h"

ColorSelector::ColorSelector( QColor color, QWidget *parent, Qt::WindowFlags f )
    : QWidget( parent, f )
    , m_color( color )
{
    setAutoFillBackground( true );
    setPalette( color );
}

ColorSelector::~ColorSelector()
{
}

QColor ColorSelector::color()
{
    return m_color;
}

void ColorSelector::mousePressEvent(QMouseEvent *)
{
    emit selected( m_color );
}
