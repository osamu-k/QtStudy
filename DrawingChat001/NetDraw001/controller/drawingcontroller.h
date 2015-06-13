#ifndef DRAWCONTROLLER_H
#define DRAWCONTROLLER_H

#include "drawingview.h"
#include "shape.h"
#include "shapespace.h"
#include "shapemaker.h"

#include <QMouseEvent>
#include <QObject>

class DrawingController : public QObject
{
    Q_OBJECT

public:
    DrawingController( ShapeSpace *shapeSpace );
    ~DrawingController();

    void setView( DrawingView *view );

    void clear();

    void setShapeType(Shape::Type shapeType){ m_shapeType = shapeType; }
    Shape::Type shapeType() const { return m_shapeType; }

    DrawingSettings &drawingSettings() { return m_settings; }

//    void writeTo( QDataStream &out );
//    void readFrom( QDataStream &in );

    bool eventFilter(QObject *obj, QEvent *event);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QMouseEvent *logicalMouseEvent( QMouseEvent *event );

    DrawingView *m_view;
    Shape::Type m_shapeType;
    DrawingSettings m_settings;
    QMap<Shape::Type,ShapeMaker *> m_shapeMakerMap;
    ShapeSpace *m_shapeSpace;
};

#endif // DRAWCONTROLLER_H
