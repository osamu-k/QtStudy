#ifndef DRAWINGVIEW_H
#define DRAWINGVIEW_H

#include <QList>
#include <QWidget>

#include "shapespace.h"

class DrawingView : public QWidget
{
    Q_OBJECT

public:
    DrawingView( ShapeSpace *shapeSpace );
    ~DrawingView();
    QSize sizeHint() const { return QSize(500,500); }

    void setOriginalSize( QSize size );
    QSize originalSize() const { return m_originalSize; }

    void setScale(qreal scale);
    qreal scale() const { return m_scale; }

    QPoint logicalPoint( QPoint p );
    QPointF logicalPoint( QPointF p );

    void addWorkingShape( Shape *shape );
    void removeWorkngShape( Shape *shape );

protected:
    void paintEvent(QPaintEvent *);

private:
    ShapeSpace *m_shapeSpace;
    QList<Shape *> m_workingShape;
    QSize m_originalSize;
    qreal m_scale;
};

#endif // DRAWINGVIEW_H
