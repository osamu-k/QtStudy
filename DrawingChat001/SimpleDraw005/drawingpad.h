#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <QList>
#include <QMap>
#include <QPolygon>
#include <QWidget>

#include "drawingsettings.h"
#include "shape.h"
#include "shapemaker.h"

class DrawingPad : public QWidget
{
    Q_OBJECT

public:
    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();
    QSize sizeHint() const { return QSize(500,500); }

    void setShapeType(Shape::Type shapeType){ m_shapeType = shapeType; }
    Shape::Type shapeType() const { return m_shapeType; }

    DrawingSettings &drawingSettings() { return m_settings; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private slots:
    void newShape();

private:
    Shape::Type m_shapeType;
    DrawingSettings m_settings;
    QMap<Shape::Type,ShapeMaker *> m_shapeMakerMap;
    QList<Shape *> m_shapeList;
};

#endif // DRAWINGPAD_H
