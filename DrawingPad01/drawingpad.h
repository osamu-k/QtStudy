#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <QMap>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>

#include "drawingmodel.h"
#include "shape.h"
#include "shapemaker.h"

class DrawingPad : public QWidget
        //, public DrawingModelObserver
{
    Q_OBJECT

public:
    enum ShapeType {
        SHAPE_FREEHAND,
        SHAPE_RECTANGLE
    };

    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();
    void setModel(DrawingModel *model);
    void setShapeType(ShapeType shapeType);

//    void notifyDrawingChanged();

protected:
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );

    void paintEvent(QPaintEvent *);

private slots:
    void drawingChanged();

private:
    DrawingModel *m_model;
    ShapeType m_shapeType;
    QMap<enum ShapeType, ShapeMaker *> m_makerMap;
};

#endif // DRAWINGPAD_H
