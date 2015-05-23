#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QDataStream>
//#include <QPainter>
#include <QRect>

#include "shapehandler.h"

class Shape
{
public:
    Shape(int type);
    virtual ~Shape();
    void setId(qint64 id);
    qint64 id();
    int type();
    void setColor(QColor color);
    QColor color();
    void setWidth(int width);
    int width();
//    virtual void draw(QPainter &painter) = 0;
    virtual QRect boundingRect() = 0;
    virtual bool hitTest(QPoint pos);
    virtual void shift(QPoint diff) = 0;
    virtual void writeTo( QDataStream &outStream );
    virtual void readFrom( QDataStream &inStream );

    virtual void handle(ShapeHandler *handler) = 0;

protected:
    qint64 m_id;
    int m_type;
    QColor m_color;
    int m_width;
};

#endif // SHAPE_H
