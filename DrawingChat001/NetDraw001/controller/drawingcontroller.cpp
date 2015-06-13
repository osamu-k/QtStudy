#include "drawingcontroller.h"

#include "freehandmaker.h"
#include "rectanglemaker.h"
#include "netshapespace.h"

DrawingController::DrawingController( ShapeSpace *shapeSpace )
    : m_shapeType(Shape::TYPE_FREEHAND)
    , m_shapeSpace(shapeSpace)
{
//    m_shapeSpace = NetShapeSpace::instance();

    FreeHandMaker *freeHandMaker = new FreeHandMaker( &m_settings );
    RectangleMaker *rectangleMaker = new RectangleMaker( &m_settings );

    m_shapeMakerMap[Shape::TYPE_FREEHAND] = freeHandMaker;
    m_shapeMakerMap[Shape::TYPE_RECTANGLE] = rectangleMaker;

    m_settings.setLineColor(Qt::black);
    m_settings.setLineWidth(0);
}

DrawingController::~DrawingController()
{
    foreach( ShapeMaker *maker, m_shapeMakerMap.values() ){
        delete maker;
    }
    m_shapeMakerMap.clear();
}

void DrawingController::setView( DrawingView *view )
{
    m_view = view;
    m_view->installEventFilter(this);

    foreach( ShapeMaker *shape, m_shapeMakerMap.values() ){
        shape->setView(view);
    }
}

void DrawingController::clear()
{
    m_shapeSpace->clear();
}

bool DrawingController::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_view){
        switch(event->type()){
        case QEvent::MouseButtonPress:
            mousePressEvent(dynamic_cast<QMouseEvent *>(event));
            return true;
        case QEvent::MouseMove:
            mouseMoveEvent(dynamic_cast<QMouseEvent *>(event));
            return true;
        case QEvent::MouseButtonRelease:
            mouseReleaseEvent(dynamic_cast<QMouseEvent *>(event));
            return true;
        default:
            break;
        }
    }
    return false;
}

void DrawingController::mousePressEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker ){
        QMouseEvent *logical = logicalMouseEvent(event);
        maker->mousePressEvent(logical);
        delete logical;
    }
}

void DrawingController::mouseMoveEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker ){
        QMouseEvent *logical = logicalMouseEvent(event);
        maker->mouseMoveEvent(logical);
        delete logical;
    }
}

void DrawingController::mouseReleaseEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker ){
        QMouseEvent *logical = logicalMouseEvent(event);
        maker->mouseReleaseEvent(logical);
        delete logical;
    }
}

QMouseEvent *DrawingController::logicalMouseEvent( QMouseEvent *event )
{
    return new QMouseEvent(
        event->type(),
        m_view->logicalPoint( event->localPos() ),
        event->windowPos(),
        event->screenPos(),
        event->button(),
        event->buttons(),
        event->modifiers() );
}

//void DrawingController::writeTo( QDataStream &out )
//{
//    m_shapeSpace->writeTo(out);
//}

//void DrawingController::readFrom( QDataStream &in )
//{
//    m_shapeSpace->readFrom(in);
//}
