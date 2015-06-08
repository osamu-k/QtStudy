#include "drawingpad.h"

#include <QDebug>
#include <QMoveEvent>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_lineColor(Qt::red)
    , m_lineWidth(5)
    , m_scale(1.0)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);
}

DrawingPad::~DrawingPad()
{
}

void DrawingPad::mousePressEvent(QMouseEvent *event)
{
    m_polygon.clear();
    m_polygon.push_back(logicalPoint(event->pos()));
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    m_polygon.push_back(logicalPoint(event->pos()));
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    m_polygon.push_back(logicalPoint(event->pos()));
    m_shapeList.push_back(m_polygon);
    m_polygon.clear();
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.scale(m_scale,m_scale);
    painter.setPen(QPen(m_lineColor,m_lineWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    foreach(QPolygon polygon, m_shapeList){
        painter.drawPolyline(polygon);
    }
    painter.drawPolyline(m_polygon);
}

void DrawingPad::setOriginalSize(QSize size)
{
    m_originalSize = size;
    int w = m_originalSize.width() * m_scale;
    int h = m_originalSize.height() * m_scale;
    setFixedSize( w, h );
    update();
}

void DrawingPad::setScale( qreal scale )
{
    m_scale = scale;
    int w = m_originalSize.width() * m_scale;
    int h = m_originalSize.height() * m_scale;
    setFixedSize( w, h );
    update();
}

QPoint DrawingPad::logicalPoint( QPoint p )
{
    return QPoint( (p.x() / m_scale),
                   (p.y() / m_scale) );
}
