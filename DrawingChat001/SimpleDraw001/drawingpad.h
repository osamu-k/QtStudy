#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <QList>
#include <QPolygon>
#include <QWidget>

class DrawingPad : public QWidget
{
    Q_OBJECT

public:
    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();
    QSize sizeHint() const { return QSize(500,500); }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QColor m_lineColor;
    int m_lineWidth;
    QPolygon m_currentShape;
    QList<QPolygon> m_shapeList;
};

#endif // DRAWINGPAD_H
