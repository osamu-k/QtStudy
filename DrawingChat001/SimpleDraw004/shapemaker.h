#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include "shape.h"

#include <QMouseEvent>
#include <QObject>
#include <QPainter>

class ShapeMaker : public QObject
{
    Q_OBJECT

public:
    ShapeMaker();
    virtual ~ShapeMaker();

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void draw(QPainter &painter) const = 0;

    virtual Shape *takeShape() = 0;

    void setLineColor(QColor color){ m_lineColor = color; }
    QColor lineColor(){ return m_lineColor; }

    void setLineWidth(int width) { m_lineWidth = width; }
    int lineWidth(){ return m_lineWidth; }

signals:
    void newShapeAvailable();

protected:
    QColor m_lineColor;
    int m_lineWidth;
};

#endif // SHAPEMAKER_H
