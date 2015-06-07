#ifndef SHAPESPACE_H
#define SHAPESPACE_H

#include "shape.h"

#include <QDataStream>
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

    void addShape( Shape *shape );
    int shapeCount() const;
    Shape *shape( int index ) const;
    void clear();

signals:
    void changed();

private:
    static ShapeSpace *m_instance;
    QVector<Shape *> m_shapeVector;
};

#endif // SHAPESPACE_H
