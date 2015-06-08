#ifndef SHAPESPACE_H
#define SHAPESPACE_H

#include "freehand.h"
#include "rectangle.h"
#include "shape.h"
#include "shapefactory.h"

#include <QDataStream>
#include <QMap>
#include <QObject>
#include <QVector>

class ShapeSpace : public QObject
{
    Q_OBJECT

private:
    ShapeSpace();
    ~ShapeSpace();

public:
    static ShapeSpace *instance();

    Shape *newShape( Shape::Type type );

    int shapeCount() const;
    Shape *shape( int index ) const;
    void clear();

    void writeTo( QDataStream &out ) const;
    void readFrom( QDataStream &in );

signals:
    void changed();

private:
    void addShape( Shape *shape );

    static ShapeSpace *m_instance;
    QVector<Shape *> m_shapeVector;

    QMap<Shape::Type, ShapeFactory *> m_factoryMap;
};

#endif // SHAPESPACE_H
