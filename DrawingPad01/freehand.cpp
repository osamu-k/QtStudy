#include "freehand.h"
#include "shapetypes.h"

FreeHand::FreeHand()
    :Shape(SHAPE_TYPE_FREEHAND)
{

}

FreeHand::~FreeHand()
{

}

void FreeHand::addPoint(QPoint point)
{
    m_pointList << point;
}

QVector<QPoint> FreeHand::points()
{
    return m_pointList;
}

//void FreeHand::draw(QPainter &painter)
//{
//    painter.save();
//    QPen pen(m_color);
//    pen.setWidth(m_width);
//    pen.setCapStyle( Qt::RoundCap );
//    painter.setPen(pen);
//    for( int i = 1; i < m_pointList.size(); i++ ){
//        painter.drawLine(m_pointList[i-1],m_pointList[i]);
//    }
//    painter.restore();
//}

void FreeHand::handle(ShapeHandler *handler)
{
    handler->handleShape(this);
}

void FreeHand::writeTo( QDataStream &outStream )
{
    Shape::writeTo(outStream);
    outStream << m_pointList.size();
    foreach( QPoint point, m_pointList ){
        outStream << point;
    }
}

void FreeHand::readFrom( QDataStream &inStream )
{
    Shape::readFrom(inStream);
    int size;
    inStream >> size;
    for(int i = 0; i<size; i++){
        QPoint point;
        inStream >> point;
        addPoint(point);
    }
}
