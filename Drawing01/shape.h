/**
shape.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QPainter>

class Shape
{
public:
    Shape();
    virtual ~Shape();
    void setLineColor( QColor );
    QColor lineColor();
    void setLineWidth( int );
    int lineWidth();
    virtual void draw( QPainter & );
protected:
    QColor m_lineColor;
    QColor m_fillColor;
    int m_lineWidth;
};

#endif // SHAPE_H
