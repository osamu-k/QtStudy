#include "drawingpad.h"

#include "freehandmaker.h"
#include "rectanglemaker.h"

#include <QDebug>
#include <QPainter>

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_shapeType(Shape::TYPE_FREEHAND)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);

    FreeHandMaker *freeHandMaker = new FreeHandMaker( &m_settings );
    RectangleMaker *rectangleMaker = new RectangleMaker( &m_settings );

    m_shapeMakerMap[Shape::TYPE_FREEHAND] = freeHandMaker;
    m_shapeMakerMap[Shape::TYPE_RECTANGLE] = rectangleMaker;

    connect(freeHandMaker,SIGNAL(newShape()),this,SLOT(newShape()));
    connect(rectangleMaker,SIGNAL(newShape()),this,SLOT(newShape()));

    m_settings.setLineColor(Qt::black);
    m_settings.setLineWidth(0);
}

DrawingPad::~DrawingPad()
{
    foreach( ShapeMaker *maker, m_shapeMakerMap.values() ){
        delete maker;
    }
    m_shapeMakerMap.clear();

    foreach( Shape *shape, m_shapeList ){
        delete shape;
    }
    m_shapeList.clear();
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

void DrawingPad::newShape()
{
    ShapeMaker *maker = qobject_cast<ShapeMaker *>(sender());
    m_shapeList.push_back(maker->takeShape());
}

void DrawingPad::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach(Shape *shape, m_shapeList)
        shape->draw(painter);
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker )
        maker->draw(painter);
}
