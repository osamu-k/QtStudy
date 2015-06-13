#include "freehandmaker.h"

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
    m_freeHand = new FreeHand();
    m_freeHand->setDrawingSettings(*m_settings);
    m_freeHand->addPoint(event->pos());
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
    emit newShape();
}

void FreeHandMaker::draw(QPainter &painter) const
{
    if( m_freeHand ){
        painter.save();
        m_freeHand->draw(painter);
        painter.restore();
    }
}

Shape *FreeHandMaker::takeShape()
{
    Shape *shape = m_freeHand;
    m_freeHand = 0;
    return shape;
}