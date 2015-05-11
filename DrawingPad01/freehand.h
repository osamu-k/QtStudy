#ifndef FREEHAND_H
#define FREEHAND_H

#include <QColor>
//#include <QPainter>
#include <QPoint>
#include <QVector>

#include "shape.h"
#include "shapehandler.h"

class FreeHand : public Shape
{
public:
    FreeHand();
    ~FreeHand();
    void addPoint(QPoint point);
    QVector<QPoint> points();
//    void draw(QPainter &painter);
    void handle(ShapeHandler *handler);
    void writeTo( QDataStream &outStream );
    void readFrom( QDataStream &inStream );

private:
    QVector<QPoint> m_pointList;
};

#endif // FREEHAND_H
