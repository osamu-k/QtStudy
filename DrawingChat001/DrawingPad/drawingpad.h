#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <Qlist>
#include <QMap>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>

#include "drawingmodel.h"
#include "shape.h"
#include "shapemaker.h"
#include "shapemanipulator.h"

class DrawingPad : public QWidget
        //, public DrawingModelObserver
{
    Q_OBJECT

public:
    enum ShapeType {
        SHAPE_UNKNOWN,
        SHAPE_FREEHAND,
        SHAPE_IMAGE,
        SHAPE_RECTANGLE
    };

    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();
    void setModel(DrawingModel *model);
    void setShapeType(ShapeType shapeType);

//    void notifyDrawingChanged();
public:
    void moveShape();

protected:
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );

    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void paintEvent(QPaintEvent *);

private slots:
    void newShape(Shape *shape);
    void drawingChanged();

private:
    void loadPixmap(QString filename,QPoint position);

    DrawingModel *m_model;
    ShapeType m_shapeType;
    Shape *m_selectedShape;
    QPoint m_lastPos;
    QMap<enum ShapeType, ShapeMaker *> m_makerMap;
    QList<ShapeManipulator *> m_manipulatorList;
    ShapeManipulator *m_dragAndDropManipulator;
};

#endif // DRAWINGPAD_H
