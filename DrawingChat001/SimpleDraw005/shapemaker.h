#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include "shape.h"
#include "drawingsettings.h"

#include <QMouseEvent>
#include <QObject>
#include <QPainter>

class ShapeMaker : public QObject
{
    Q_OBJECT

public:
    ShapeMaker( DrawingSettings *settings );
    virtual ~ShapeMaker();

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void draw(QPainter &painter) const = 0;

    virtual Shape *takeShape() = 0;

signals:
    void newShape();

protected:
    DrawingSettings *m_settings;
};

#endif // SHAPEMAKER_H