#include "freehandmaker.h"
#include "shapepainter.h"

FreeHandMaker::FreeHandMaker()
    :m_freeHand(0)
{

}

FreeHandMaker::~FreeHandMaker()
{

}

void FreeHandMaker::begin(QPoint point)
{
    m_freeHand = new FreeHand;
    m_freeHand->setColor(Qt::red);
    m_freeHand->setWidth(5);
    m_freeHand->addPoint(point);
}

void FreeHandMaker::move(QPoint point)
{
    if( m_freeHand){
        m_freeHand->addPoint(point);
    }
}

Shape *FreeHandMaker::end(QPoint point)
{
    Shape *shape = 0;
    if( m_freeHand ){
        m_freeHand->addPoint(point);
        m_freeHand->setColor(Qt::blue);
        m_freeHand->setWidth(10);
        shape = m_freeHand;
        m_freeHand = 0;
    }
    return shape;
}

void FreeHandMaker::draw(QPainter &painter)
{
    ShapePainter shapePainter(painter);
    if( m_freeHand ){
//        m_freeHand->draw(painter);
        m_freeHand->handle(&shapePainter);
    }
}
