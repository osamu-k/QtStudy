#include "drawingpad.h"

#include <QDebug>
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
    m_freeHand.clearPoints();
    m_freeHand.setLineColor(m_lineColor);
    m_freeHand.setLineWidth(m_lineWidth);
    m_freeHand.addPoint(event->pos());
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    m_freeHand.addPoint(event->pos());
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    m_freeHand.addPoint(event->pos());
    m_shapeList.push_back(m_freeHand);
    m_freeHand.clearPoints();
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach(FreeHand freeHand, m_shapeList){
        freeHand.draw(painter);
    }
    m_freeHand.draw(painter);
}
