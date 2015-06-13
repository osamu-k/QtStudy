#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include "shape.h"
#include "drawingsettings.h"
#include "drawingview.h"

#include <QDataStream>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>

class ShapeMaker : public QObject
{
    Q_OBJECT

public:
    ShapeMaker( DrawingSettings *settings );
    virtual ~ShapeMaker();

    Shape *newShape( Shape::Type type );
    void shapeChanged( Shape *shape );
    void shapeCompleted( Shape *shape );
    void shapeCanceled( Shape *shape );

    void setView( DrawingView *view ){ m_view = view; }

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual bool readFrom( QDataStream &in, Shape::Type type ) = 0;

protected:
    DrawingSettings *m_settings;
    DrawingView *m_view;
};

#endif // SHAPEMAKER_H
