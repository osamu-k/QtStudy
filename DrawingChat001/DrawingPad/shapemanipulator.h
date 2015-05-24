#ifndef SHAPEMANIPULATOR_H
#define SHAPEMANIPULATOR_H

#include "shape.h"

#include <QObject>
#include <QRegion>

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QPainter>

class ShapeManipulator : public QObject
{
    Q_OBJECT

public:
    ShapeManipulator();
    ~ShapeManipulator();

    virtual bool dragEnterEvent(QDragEnterEvent *){ return false; }
    virtual bool dragLeaveEvent(QDragLeaveEvent *){ return false; }
    virtual bool dragMoveEvent(QDragMoveEvent *){ return false; }
    virtual bool dropEvent(QDropEvent *){ return false; }

    virtual void draw(QPainter &){}

signals:
    void updateRegion(QRegion &region);
    void newShape(Shape *shape);
};

#endif // SHAPEMANIPULATOR_H
