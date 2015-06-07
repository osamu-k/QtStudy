#ifndef DRAWINGVIEW_H
#define DRAWINGVIEW_H

#include <QWidget>

#include "shapespace.h"

class DrawingView : public QWidget
{
    Q_OBJECT

public:
    DrawingView();
    ~DrawingView();
    QSize sizeHint() const { return QSize(500,500); }

protected:
    void paintEvent(QPaintEvent *);

private:
    ShapeSpace *m_shapeSpace;
};

#endif // DRAWINGVIEW_H
