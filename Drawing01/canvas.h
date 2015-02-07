/**
canvas.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QWidget>

#include "polyline.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

signals:
    void dataAdded( QByteArray );

public slots:
    void setLineColor( QColor );
    void setLineWidth( int );
    void clear();
    void writeTo( QDataStream & ) const;
    void readFrom( QDataStream & );
    void addData( QByteArray );

protected:
    void paintEvent( QPaintEvent * );
    void mousePressEvent( QMouseEvent * );
    void mouseMoveEvent( QMouseEvent * );
    void mouseReleaseEvent( QMouseEvent * );

private:
    void clearLineList();

    QColor m_lineColor;
    int m_lineWidth;

    PolyLine *m_polyLine;
    QList<PolyLine *> m_polyLineList;
};

#endif // CANVAS_H
