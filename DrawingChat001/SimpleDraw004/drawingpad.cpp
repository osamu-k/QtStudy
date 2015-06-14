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

    FreeHandMaker *freeHandMaker = new FreeHandMaker();
    RectangleMaker *rectangleMaker = new RectangleMaker();

    m_shapeMakerMap[Shape::TYPE_FREEHAND] = freeHandMaker;
    m_shapeMakerMap[Shape::TYPE_RECTANGLE] = rectangleMaker;

    connect(freeHandMaker,SIGNAL(newShapeAvailable()),this,SLOT(newShapeAvailable()));
    connect(rectangleMaker,SIGNAL(newShapeAvailable()),this,SLOT(newShapeAvailable()));

    setLineColor(Qt::black);
    setLineWidth(0);
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

void DrawingPad::setLineColor(QColor color)
{
    m_lineColor = color;
    foreach( ShapeMaker *maker, m_shapeMakerMap.values() )
        maker->setLineColor(color);
}

void DrawingPad::setLineWidth(int width)
{
    m_lineWidth = width;
    foreach( ShapeMaker *maker, m_shapeMakerMap.values() )
        maker->setLineWidth(width);
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

void DrawingPad::newShapeAvailable()
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
