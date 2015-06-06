#ifndef DRAWINGMODEL_H
#define DRAWINGMODEL_H

#include <QDataStream>
#include <QList>
#include <QObject>
#include "drawingserver.h"
#include "shape.h"

#include "broadcastclient.h"

//class DrawingModelObserver
//{
//public:
//    virtual void notifyDrawingChanged() = 0;
//};

class DrawingModel : public QObject
{
    Q_OBJECT

public:
    DrawingModel();
    ~DrawingModel();
    void addShape(Shape *shape);
    void slideShape(Shape *shape, QPoint diff);
    QList<Shape *> shapeList();
    void clear();
    void writeTo( QDataStream &outStream );
    void readFrom( QDataStream &inStream );
    void connectToHost();
    void disconnectFromtHost();
//    void addObserver(DrawingModelObserver *observer);
//    void removeObserver(DrawingModelObserver *observer);
    Shape *select(QPoint pos);

signals:
    void drawingChanged();

private slots:
    void dataReceived(QByteArray data);

private:
    void clearList();
    Shape *readShape(QDataStream &inStream);
//    void notify();
    QList<Shape *> m_shapeList;
//    QList<DrawingModelObserver *> m_observerList;
    BroadcastClient m_broadcastClient;
};

#endif // DRAWINGMODEL_H
