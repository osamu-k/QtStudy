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

    void setOriginalSize( QSize size );
    QSize originalSize() const { return m_originalSize; }

    void setScale(qreal scale);
    qreal scale() const { return m_scale; }

    QPoint logicalPoint( QPoint p );

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QColor m_lineColor;
    int m_lineWidth;
    QPolygon m_polygon;
    QList<QPolygon> m_shapeList;
    QSize m_originalSize;
    qreal m_scale;
};

#endif // DRAWINGPAD_H
