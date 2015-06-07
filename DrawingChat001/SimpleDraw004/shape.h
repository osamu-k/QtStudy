#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QMouseEvent>
#include <QPainter>

class Shape
{
public:
    enum Type{
        TYPE_UNDEFINED,
        TYPE_FREEHAND,
        TYPE_RECTANGLE
    };

    Shape( Type type = TYPE_UNDEFINED );
    virtual ~Shape();

    Type type() const { return m_type; }

    void setLineColor(QColor color){ m_lineColor = color; }
    QColor lineColor(){ return m_lineColor; }

    void setLineWidth(int width) { m_lineWidth = width; }
    int lineWidth(){ return m_lineWidth; }

    virtual void draw( QPainter &painter ) const = 0;

protected:
    Type m_type;
    QColor m_lineColor;
    int m_lineWidth;
};

#endif // SHAPE_H
