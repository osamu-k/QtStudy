#include "drawingcontroller.h"

#include "freehandmaker.h"
#include "rectanglemaker.h"

DrawingController::DrawingController()
    :m_shapeType(Shape::TYPE_FREEHAND)
{
    m_shapeSpace = ShapeSpace::instance();

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
        QMouseEvent logicalEvent(
            event->type(),
            m_view->logicalPoint( event->localPos() ),
            event->windowPos(),
            event->screenPos(),
            event->button(),
            event->buttons(),
            event->modifiers() );
        maker->mousePressEvent(&logicalEvent);
    }
}

void DrawingController::mouseMoveEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker ){
        QMouseEvent logicalEvent(
            event->type(),
            m_view->logicalPoint( event->localPos() ),
            event->windowPos(),
            event->screenPos(),
            event->button(),
            event->buttons(),
            event->modifiers() );
        maker->mouseMoveEvent(&logicalEvent);
    }
}

void DrawingController::mouseReleaseEvent(QMouseEvent *event)
{
    ShapeMaker *maker = m_shapeMakerMap[m_shapeType];
    if( maker ){
        QMouseEvent logicalEvent(
            event->type(),
            m_view->logicalPoint( event->localPos() ),
            event->windowPos(),
            event->screenPos(),
            event->button(),
            event->buttons(),
            event->modifiers() );
        maker->mouseReleaseEvent(&logicalEvent);
    }
}

void DrawingController::writeTo( QDataStream &out )
{
    m_shapeSpace->writeTo(out);
}

void DrawingController::readFrom( QDataStream &in )
{
    m_shapeSpace->readFrom(in);
}
