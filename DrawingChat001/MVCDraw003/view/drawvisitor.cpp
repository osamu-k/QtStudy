#include "drawvisitor.h"

#include "freehand.h"
#include "rectangle.h"

DrawVisitor::DrawVisitor( QPainter &painter )
    : m_painter(painter)
{

}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::visit( FreeHand *freeHand )
{
    m_painter.save();
    DrawingSettings settings = freeHand->drawingSettings();
    m_painter.setPen(QPen(settings.lineColor(),settings.lineWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if( settings.isFillColorEnabled()){
        m_painter.setBrush(QBrush(settings.fillColor()));
        if( ! settings.isOutlineEnabled() ){
            m_painter.setPen(Qt::NoPen);
        }
        m_painter.drawPolygon(freeHand->polygon());
    }
    else if( settings.isOutlineEnabled() ){
        m_painter.drawPolyline(freeHand->polygon());
    }
    m_painter.restore();
}

void DrawVisitor::visit( Rectangle *rectangle )
{
    m_painter.save();
    QPoint point1 = rectangle->point1();
    QPoint point2 = rectangle->point2();
    QRect rect( point1.x(), point1.y(),
                point2.x() - point1.x(), point2.y() - point1.y() );

    DrawingSettings settings = rectangle->drawingSettings();
    if( settings.isFillColorEnabled()){
        m_painter.fillRect(rect,QBrush(settings.fillColor()));
    }
    if( settings.isOutlineEnabled()){
        m_painter.setPen(QPen(settings.lineColor(),settings.lineWidth()));
        m_painter.drawRect(rect);
    }
    m_painter.restore();
}
