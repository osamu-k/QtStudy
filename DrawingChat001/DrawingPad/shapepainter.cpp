#include "freehand.h"
#include "freehandpainter.h"
#include "image.h"
#include "imagepainter.h"
#include "rectangle.h"
#include "rectanglepainter.h"
#include "shapepainter.h"

ShapePainter::ShapePainter(QPainter &painter)
    : m_painter(painter)
{

}

ShapePainter::~ShapePainter()
{

}

void ShapePainter::handleShape( FreeHand *shape )
{
    FreeHandPainter painter;
    painter.draw(m_painter,shape);

//    m_painter.save();
//    QPen pen(shape->color());
//    pen.setWidth(shape->width());
//    pen.setCapStyle( Qt::RoundCap );
//    m_painter.setPen(pen);

//    QVector<QPoint> points = shape->points();
//    for( int i = 1; i < points.size(); i++ ){
//        m_painter.drawLine(points[i-1],points[i]);
//    }
//    m_painter.restore();
}

void ShapePainter::handleShape( Rectangle *shape )
{
    RectanglePainter painter;
    painter.draw(m_painter,shape);

//    m_painter.save();
//    QPen pen(shape->color());
//    pen.setWidth(shape->width());
////    pen.setCapStyle( Qt::RoundCap );
//    m_painter.setPen(pen);
//    QBrush brush(shape->fillColor());
//    m_painter.setBrush(brush);
//    m_painter.drawRect(QRect(shape->point1(),shape->point2()));
//    m_painter.restore();
}

void ShapePainter::handleShape(Image *shape)
{
    ImagePainter painter;
    painter.draw(m_painter,shape);
}
