#ifndef IMAGE_H
#define IMAGE_H

#include "shape.h"
#include <QPixmap>

class Image : public Shape
{
public:
    Image();
    ~Image();
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap();
    void setPosition(QPoint position);
    QPoint position();
    void setSize(QSize size);
    QSize size();
//    void draw(QPainter &painter);
    QRect boundingRect();
    void shift(QPoint diff);
    void writeTo( QDataStream &outStream );
    void readFrom( QDataStream &inStream );
    void handle(ShapeHandler *handler);

private:
    QPixmap m_pixmap;
    QPoint m_position;
    QSize m_size;
};

#endif // IMAGE_H
