/**
polyline.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "polyline.h"

PolyLine::PolyLine()
{

}

PolyLine::~PolyLine()
{

}

void PolyLine::addPoint( QPoint point )
{
    m_points << point;
}

void PolyLine::draw(QPainter &painter)
{
    painter.save();

    QPen pen;
    pen.setColor( m_lineColor );
    pen.setWidth( m_lineWidth );
    pen.setCapStyle( Qt::RoundCap );
    painter.setPen( pen );

    QList<QPoint>::iterator lineIterator = m_points.begin();
    if( lineIterator != m_points.end() ){
        QPoint point = *(lineIterator++);
        while( lineIterator != m_points.end() ){
            painter.drawLine( point, *lineIterator );
            point = *(lineIterator++);
        }
    }

    painter.restore();
}

void PolyLine::writeTo(QDataStream &out) const
{
    out << m_lineColor;
    out << m_fillColor;
    out << m_lineWidth;
    out << m_points.size();
    foreach( QPoint point, m_points ){
        out << point;
    }
}

void PolyLine::readFrom(QDataStream &in)
{
    in >> m_lineColor;
    in >> m_fillColor;
    in >> m_lineWidth;
    int nPoints = 0;
    in >> nPoints;
    m_points.clear();
    for( int i = 0; i < nPoints; i++ ){
        QPoint point;
        in >> point;
        m_points << point;
    }
}

void operator<<( QDataStream &out, const PolyLine &polyLine )
{
    polyLine.writeTo( out );
}

void operator>>( QDataStream &in, PolyLine &polyLine )
{
    polyLine.readFrom( in );
}

