#include "drawingpad.h"

#include "freehandmaker.h"
#include "rectanglemaker.h"

#include <QDebug>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_shapeType(Shape::TYPE_FREEHAND)
    , m_shapeSpace(0)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);

    m_shapeSpace = ShapeSpace::instance();
    connect(m_shapeSpace, SIGNAL(changed()),this,SLOT(update()));

    FreeHandMaker *freeHandMaker = new FreeHandMaker( &m_settings );
    RectangleMaker *rectangleMaker = new RectangleMaker( &m_settings );

    m_shapeMakerMap[Shape::TYPE_FREEHAND] = freeHandMaker;
    m_shapeMakerMap[Shape::TYPE_RECTANGLE] = rectangleMaker;

    m_settings.setLineColor(Qt::black);
    m_settings.setLineWidth(0);
}

DrawingPad::~DrawingPad()
{
    foreach( ShapeMaker *maker, m_shapeMakerMap.values() ){
        delete maker;
    }
    m_shapeMakerMap.clear();

    m_shapeSpace->clear();
}

void DrawingPad::clear()
{
    m_shapeSpace->clear();
    update();
}

void DrawingPad::mousePressEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker )
        maker->mousePressEvent(event);
    update();
}

void DrawingPad::mouseMoveEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker )
        maker->mouseMoveEvent(event);
    update();
}

void DrawingPad::mouseReleaseEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker )
        maker->mouseReleaseEvent(event);
    update();
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for( int i = 0; i < m_shapeSpace->shapeCount(); i++ ){
        Shape *shape = m_shapeSpace->shape(i);
        shape->draw(painter);
    }
}

void DrawingPad::writeTo( QDataStream &out )
{
    m_shapeSpace->writeTo(out);
}

void DrawingPad::readFrom( QDataStream &in )
{
    m_shapeSpace->readFrom(in);
}
