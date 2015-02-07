/**
widthselector.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef WIDTHSELECTOR_H
#define WIDTHSELECTOR_H

#include <QWidget>

class WidthSelector : public QWidget
{
    Q_OBJECT
public:
    explicit WidthSelector( int width, QWidget *parent = 0, Qt::WindowFlags f = 0 );
    ~WidthSelector();
    int lineWidth();
    void setSelected( bool );

signals:
    void selected( int );

public slots:
    void setColor( QColor );

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    int m_width;
    bool m_selected;
    QColor m_color;
};

#endif // WIDTHSELECTOR_H
