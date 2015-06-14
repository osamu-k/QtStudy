#include "drawingpad.h"

#include <QMouseEvent>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_lineColor(Qt::black)
    , m_lineWidth(0)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);
}

DrawingPad::~DrawingPad()
{
}

void DrawingPad::mousePressEvent(QMouseEvent *event)
{
    m_currentShape.clearPoints();
    m_currentShape.setLineColor(m_lineColor);
    m_currentShape.setLineWidth(m_lineWidth);
    m_currentShape.addPoint(event->pos());
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    m_currentShape.addPoint(event->pos());
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    m_currentShape.addPoint(event->pos());
    m_shapeList.push_back(m_currentShape);
    m_currentShape.clearPoints();
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach(FreeHand freeHand, m_shapeList){
        freeHand.draw(painter);
    }
    m_currentShape.draw(painter);
}
