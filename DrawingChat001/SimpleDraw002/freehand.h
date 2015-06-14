#ifndef FREEHAND_H
#define FREEHAND_H

#include <QColor>
#include <QPainter>
#include <QPolygon>

class FreeHand
{
public:
    FreeHand();
    ~FreeHand();

    void setLineColor(QColor color){ m_lineColor = color; }
    QColor lineColor() const { return m_lineColor; }

    void setLineWidth(int width) { m_lineWidth = width; }
    int lineWidth() const { return m_lineWidth; }

    void addPoint(QPoint point);
    void clearPoints() { m_polygon.clear(); }

    void draw(QPainter &painter) const;

private:
    QColor m_lineColor;
    int m_lineWidth;
    QPolygon m_polygon;
};

#endif // FREEHAND_H
