#ifndef DRAWINGSERVER_H
#define DRAWINGSERVER_H

#include <QObject>
#include <QList>
#include "shape.h"

class DrawingServer : public QObject
{
    Q_OBJECT
public:
    static DrawingServer *instance();
    void addShape(Shape *shape);
    QList<Shape*> shapeList();
    void clear();
signals:
    void drawingChanged();
//    void shapeAdded(Shape *shape);
//    void cleared();
private:
    DrawingServer();
    ~DrawingServer();
private:
    void clearList();
    static DrawingServer *m_instance;
    QList<Shape *> m_shapeList;
};

#endif // DRAWINGSERVER_H
