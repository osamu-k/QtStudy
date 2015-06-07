#include "drawingview.h"

#include <QDebug>

DrawingView::DrawingView()
{
    setAutoFillBackground(true);
    setPalette(Qt::white);

    m_shapeSpace = ShapeSpace::instance();
    connect(m_shapeSpace, SIGNAL(changed()),this,SLOT(update()));
}

DrawingView::~DrawingView()
{

}

void DrawingView::paintEvent(QPaintEvent *)
{
    qDebug() << "DrawingView::paintEvent";
    QPainter painter(this);
    DrawVisitor visitor(painter);
    for( int i = 0; i < m_shapeSpace->shapeCount(); i++ ){
        Shape *shape = m_shapeSpace->shape(i);
        qDebug() << "DrawingView::paintEvent shape->type() = " << shape->type();
        shape->accept(&visitor);
    }
}
