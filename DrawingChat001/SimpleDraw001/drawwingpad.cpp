#include "drawingpad.h"

#include <QDebug>
#include <QMoveEvent>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_lineColor(Qt::red)
    , m_lineWidth(5)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);
}

DrawingPad::~DrawingPad()
{
}

void DrawingPad::mousePressEvent(QMouseEvent *event)
{
    m_currentShape.clear();
    m_currentShape.push_back(event->pos());
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    m_currentShape.push_back(event->pos());
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    m_currentShape.push_back(event->pos());
    m_shapeList.push_back(m_currentShape);
    m_currentShape.clear();
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(m_lineColor,m_lineWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    foreach(QPolygon polygon, m_shapeList){
        painter.drawPolyline(polygon);
    }
    painter.drawPolyline(m_currentShape);
}
