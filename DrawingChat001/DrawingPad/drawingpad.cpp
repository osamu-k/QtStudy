#include <QDebug>
#include <QPainter>

#include "drawingpad.h"
#include "freehandmaker.h"
#include "imagemanipulator.h"
#include "rectanglemaker.h"
#include "shapepainter.h"
#include "shapetypes.h"
#include "image.h"

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_shapeType(SHAPE_FREEHAND)
    , m_selectedShape(0)
    , m_dragAndDropManipulator(0)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);

    m_makerMap[SHAPE_FREEHAND] = new FreeHandMaker;
    m_makerMap[SHAPE_RECTANGLE] = new RectangleMaker;

    ImageManipulator *imageManipulator = new ImageManipulator;
    connect( imageManipulator, &ShapeManipulator::newShape, this, &DrawingPad::newShape );
    connect( imageManipulator, &ShapeManipulator::updateRegion, this, (void (QWidget::*)(const QRegion &))&QWidget::update);
    m_manipulatorList << imageManipulator;

    setAcceptDrops(true);
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
//    if( m_makerMap[m_shapeType] ){
    if( m_makerMap.contains( m_shapeType ) ){
        m_makerMap[m_shapeType]->begin(event->pos());
        update();
    }
    else{
        Shape *shape = m_model->select(event->pos());
        if( shape ){
            m_selectedShape = shape;
            m_lastPos = event->pos();
        }
    }
}

void DrawingPad::mouseMoveEvent( QMouseEvent *event )
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    //    if( m_makerMap[m_shapeType] ){
    if( m_makerMap.contains( m_shapeType ) ){
        m_makerMap[m_shapeType]->move(event->pos());
        update();
    }
    else if( m_selectedShape ){
        QPoint diff = event->pos() - m_lastPos;
        QRegion region(m_selectedShape->boundingRect());
        m_selectedShape->shift(diff);
        region.united(m_selectedShape->boundingRect());
        update(region);
        m_lastPos = event->pos();

        m_model->slideShape(m_selectedShape,diff);
    }
}

void DrawingPad::mouseReleaseEvent( QMouseEvent *event )
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    //    if( m_makerMap[m_shapeType] ){
    if( m_makerMap.contains( m_shapeType ) ){
        Shape *shape = m_makerMap[m_shapeType]->end(event->pos());
        m_model->addShape( shape );
        update();
    }
    else if( m_selectedShape ){
        QPoint diff = event->pos() - m_lastPos;
        QRegion region(m_selectedShape->boundingRect());
        m_selectedShape->shift(diff);
        region.united(m_selectedShape->boundingRect());
        update(region);
        m_model->slideShape(m_selectedShape,diff);
        m_selectedShape = 0;
    }
}

void DrawingPad::dragEnterEvent(QDragEnterEvent *event)
{
    foreach( ShapeManipulator *manipulator, m_manipulatorList ){
        if( manipulator->dragEnterEvent(event) ){
            m_dragAndDropManipulator = manipulator;
            break;
        }
    }
}

void DrawingPad::dragLeaveEvent(QDragLeaveEvent *event)
{
    if( m_dragAndDropManipulator ){
        m_dragAndDropManipulator->dragLeaveEvent(event);
    }
}

void DrawingPad::dragMoveEvent(QDragMoveEvent *event)
{
    if( m_dragAndDropManipulator ){
        m_dragAndDropManipulator->dragMoveEvent(event);
    }
}

void DrawingPad::dropEvent(QDropEvent *event)
{
    if( m_dragAndDropManipulator ){
        m_dragAndDropManipulator->dropEvent(event);
        m_dragAndDropManipulator = 0;
    }
}

void DrawingPad::loadPixmap(QString filename, QPoint position)
{
    QPixmap pixmap(filename);
    Image *image = new Image();
    image->setPixmap(pixmap);
    image->setPosition(position);
    m_model->addShape(image);
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

//    if( m_makerMap[m_shapeType] ){
    if( m_makerMap.contains( m_shapeType ) ){
        m_makerMap[m_shapeType]->draw(painter);
    }

    if( m_dragAndDropManipulator ){
        m_dragAndDropManipulator->draw(painter);
    }
}

//void DrawingPad::notifyDrawingChanged()
//{
//    update();
//}

void DrawingPad::newShape(Shape *shape)
{
    if( m_model ){
        m_model->addShape(shape);
    }
}

void DrawingPad::drawingChanged()
{
    update();
}

void DrawingPad::moveShape()
{
    m_shapeType = SHAPE_UNKNOWN;
}
