#include <QDebug>
#include <QPainter>

#include "drawingpad.h"
#include "freehandmaker.h"
#include "rectanglemaker.h"
#include "shapepainter.h"

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_shapeType(SHAPE_FREEHAND)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);

    m_makerMap[SHAPE_FREEHAND] = new FreeHandMaker;
    m_makerMap[SHAPE_RECTANGLE] = new RectangleMaker;
}

DrawingPad::~DrawingPad()
{

}

void DrawingPad::setModel(DrawingModel *model)
{
    m_model = model;
//    m_model->addObserver( this );
    connect( m_model, &DrawingModel::drawingChanged, this, &DrawingPad::drawingChanged );
}

void DrawingPad::setShapeType(ShapeType shapeType)
{
    m_shapeType = shapeType;
}

void DrawingPad::mousePressEvent( QMouseEvent *event )
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    if( m_makerMap[m_shapeType] ){
        m_makerMap[m_shapeType]->begin(event->pos());
    }
    update();
}

void DrawingPad::mouseMoveEvent( QMouseEvent *event )
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    if( m_makerMap[m_shapeType] ){
        m_makerMap[m_shapeType]->move(event->pos());
    }
    update();
}

void DrawingPad::mouseReleaseEvent( QMouseEvent *event )
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    if( m_makerMap[m_shapeType] ){
        Shape *shape = m_makerMap[m_shapeType]->end(event->pos());
        m_model->addShape( shape );
    }
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    ShapePainter shapePainter(painter);

    QList<Shape *> shapeList = m_model->shapeList();
    foreach( Shape *shape, shapeList){
//        shape->draw(painter);
        shape->handle(&shapePainter);
    }

    if( m_makerMap[m_shapeType] ){
        m_makerMap[m_shapeType]->draw(painter);
    }
}

//void DrawingPad::notifyDrawingChanged()
//{
//    update();
//}

void DrawingPad::drawingChanged()
{
    update();
}
