/**
widthselector.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include <QDebug>
#include <QPainter>
#include "widthselector.h"

WidthSelector::WidthSelector( int width, QWidget *parent, Qt::WindowFlags f )
    : QWidget( parent, f )
    , m_width( width )
    , m_selected( false )
    , m_color( Qt::black )
{
    setAutoFillBackground( true );
    setPalette( Qt::white );
}

WidthSelector::~WidthSelector()
{
}

int WidthSelector::lineWidth()
{
    return m_width;
}

void WidthSelector::setSelected( bool selected )
{
    m_selected = selected;
    if( m_selected ){
        setPalette( QColor(Qt::yellow).lighter() );
    }
    else{
        setPalette( Qt::white );
    }
    update();
}

void WidthSelector::setColor( QColor color )
{
    m_color = color;
    update();
}

void WidthSelector::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    painter.setPen( m_color );
    painter.setBrush( m_color );
    painter.drawEllipse( (width() - m_width) / 2, (height() - m_width) / 2, m_width, m_width );
}

void WidthSelector::mousePressEvent(QMouseEvent *)
{
    emit selected( m_width );
}
