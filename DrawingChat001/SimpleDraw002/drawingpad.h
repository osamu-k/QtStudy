#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <QList>
#include <QPolygon>
#include <QWidget>

#include "freehand.h"

class DrawingPad : public QWidget
{
    Q_OBJECT

public:
    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();
    QSize sizeHint() const { return QSize(500,500); }

    void setLineColor(QColor color){ m_lineColor = color; }
    QColor lineColor() const { return m_lineColor; }

    void setLineWidth(int width) { m_lineWidth = width; }
    int lineWidth() const { return m_lineWidth; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private:
    QColor m_lineColor;
    int m_lineWidth;
    FreeHand m_currentShape;
    QList<FreeHand> m_shapeList;
};

#endif // DRAWINGPAD_H
