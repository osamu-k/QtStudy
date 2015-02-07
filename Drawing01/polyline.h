/**
polyline.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef POLYLINE_H
#define POLYLINE_H

#include <QDataStream>
#include "shape.h"

class PolyLine : public Shape
{
public:
    PolyLine();
    ~PolyLine();
    void addPoint( QPoint );
    void draw( QPainter & );
    void writeTo( QDataStream & ) const;
    void readFrom( QDataStream & );

private:
    QList<QPoint> m_points;
};

void operator<<( QDataStream &, const PolyLine & );
void operator>>( QDataStream &, PolyLine & );

#endif // POLYLINE_H
