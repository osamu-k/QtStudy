/**
colorselector.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QColor>
#include <QWidget>

class ColorSelector : public QWidget
{
    Q_OBJECT

public:
    ColorSelector( QColor color, QWidget *parent = 0, Qt::WindowFlags f = 0 );
    ~ColorSelector();
    QColor color();

signals:
    void selected( QColor );

protected:
    void mousePressEvent(QMouseEvent *);

private:
    QColor m_color;
};

#endif // COLORSELECTOR_H
