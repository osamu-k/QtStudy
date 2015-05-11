#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QDataStream>
//#include <QPainter>

#include "shapehandler.h"

class Shape
{
public:
    Shape(int type);
    virtual ~Shape();
    int type();
    void setColor(QColor color);
    QColor color();
    void setWidth(int width);
    int width();
//    virtual void draw(QPainter &painter) = 0;
    virtual void handle(ShapeHandler *handler) = 0;
    virtual void writeTo( QDataStream &outStream );
    virtual void readFrom( QDataStream &inStream );

protected:
    int m_type;
    QColor m_color;
    int m_width;
};

#endif // SHAPE_H
