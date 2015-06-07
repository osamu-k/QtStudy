#include "freehandmaker.h"
#include "shapespace.h"

FreeHandMaker::FreeHandMaker( DrawingSettings *settings )
    : ShapeMaker(settings)
    , m_freeHand(0)
{
}

FreeHandMaker::~FreeHandMaker()
{
}

void FreeHandMaker::mousePressEvent(QMouseEvent *event)
{
    ShapeSpace *space = ShapeSpace::instance();
    m_freeHand = dynamic_cast<FreeHand *>( space->newShape(Shape::TYPE_FREEHAND) );
    if( m_freeHand ){
        m_freeHand->setDrawingSettings(*m_settings);
        m_freeHand->addPoint(event->pos());
    }
}

void FreeHandMaker::mouseMoveEvent(QMouseEvent *event)
{
    if( m_freeHand == 0 )
        return;
    m_freeHand->addPoint(event->pos());
}

void FreeHandMaker::mouseReleaseEvent(QMouseEvent *event)
{
    if( m_freeHand == 0 )
        return;
    m_freeHand->addPoint(event->pos());
}

Shape *FreeHandMaker::takeShape()
{
    Shape *shape = m_freeHand;
    m_freeHand = 0;
    return shape;
}

bool FreeHandMaker::readFrom( QDataStream &in, Shape::Type type )
{
    if( type!= Shape::TYPE_FREEHAND )
        return false;
    m_freeHand = new FreeHand();
    m_freeHand->readFrom(in);
    return true;
}
