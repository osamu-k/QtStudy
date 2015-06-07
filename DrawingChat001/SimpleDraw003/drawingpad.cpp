#include "drawingpad.h"

#include "freehand.h"
#include "rectangle.h"

#include <QDebug>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_shapeType(Shape::TYPE_FREEHAND)
    , m_lineColor(Qt::black)
    , m_lineWidth(0)
    , m_currentShape(0)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);
}

DrawingPad::~DrawingPad()
{
    foreach( Shape *shape, m_shapeList ){
        delete shape;
    }
    m_shapeList.clear();
}

void DrawingPad::mousePressEvent(QMouseEvent *event)
{
    switch(m_shapeType){
    case Shape::TYPE_FREEHAND:
        mousePressForFreeHand(event);
        break;
    case Shape::TYPE_RECTANGLE:
        mousePressForRectangle(event);
        break;
    default:
        break;
    }
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    if( m_currentShape == 0 )
        return;
    switch(m_currentShape->type()){
    case Shape::TYPE_FREEHAND:
        mouseMoveForFreeHand(event);
        break;
    case Shape::TYPE_RECTANGLE:
        mouseMoveForRectangle(event);
        break;
    default:
        break;
    }
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    if( m_currentShape == 0 )
        return;
    switch(m_currentShape->type()){
    case Shape::TYPE_FREEHAND:
        mouseReleaseForFreeHand(event);
        break;
    case Shape::TYPE_RECTANGLE:
        mouseReleaseForRectangle(event);
        break;
    default:
        break;
    }
    update();
}

void DrawingPad::mousePressForFreeHand(QMouseEvent *event)
{
    FreeHand *freeHand = new FreeHand();
    freeHand->setLineColor( m_lineColor );
    freeHand->setLineWidth(m_lineWidth);
    freeHand->addPoint(event->pos());
    m_currentShape = freeHand;
}

void DrawingPad::mouseMoveForFreeHand(QMouseEvent *event)
{
    FreeHand *freeHand = dynamic_cast<FreeHand*>(m_currentShape);
    if( freeHand == 0 )
        return;
    freeHand->addPoint(event->pos());
}

void DrawingPad::mouseReleaseForFreeHand(QMouseEvent *event)
{
    FreeHand *freeHand = dynamic_cast<FreeHand*>(m_currentShape);
    if( freeHand == 0 )
        return;
    freeHand->addPoint(event->pos());
    m_shapeList.push_back(m_currentShape);
    m_currentShape = 0;
}

void DrawingPad::mousePressForRectangle(QMouseEvent *event)
{
    Rectangle *rectangle = new Rectangle();
    rectangle->setLineColor( m_lineColor );
    rectangle->setLineWidth(m_lineWidth);
    rectangle->setPoint1(event->pos());
    rectangle->setPoint2(event->pos());
    m_currentShape = rectangle;
}

void DrawingPad::mouseMoveForRectangle(QMouseEvent *event)
{
    Rectangle *rectangle = dynamic_cast<Rectangle*>(m_currentShape);
    if( rectangle == 0 )
        return;
    rectangle->setPoint2(event->pos());
}

void DrawingPad::mouseReleaseForRectangle(QMouseEvent *event)
{
    Rectangle *rectangle = dynamic_cast<Rectangle*>(m_currentShape);
    if( rectangle == 0 )
        return;
    rectangle->setPoint2(event->pos());
    m_shapeList.push_back(m_currentShape);
    m_currentShape = 0;
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach(Shape *shape, m_shapeList){
        shape->draw(painter);
    }
    if( m_currentShape )
        m_currentShape->draw(painter);
}
