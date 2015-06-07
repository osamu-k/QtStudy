#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QMouseEvent>
#include <QPainter>

#include "drawingsettings.h"

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

    void setDrawingSettings( DrawingSettings settings) { m_settings = settings; }
    DrawingSettings drawingSettings() const { return m_settings; }

    virtual void draw( QPainter &painter ) const = 0;

protected:
    Type m_type;
    DrawingSettings m_settings;
};

#endif // SHAPE_H
