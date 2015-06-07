#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QDataStream>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>

#include "drawingsettings.h"

class Shape : public QObject
{
    Q_OBJECT

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

    virtual void writeTo(QDataStream &out) const;
    virtual void readFrom(QDataStream &in);

signals:
    void changed();

protected:
    Type m_type;
    DrawingSettings m_settings;
};

#endif // SHAPE_H
