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

QRect FreeHand::boundingRect()
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    if( m_pointList.size() > 0){
        QPoint p0 = m_pointList[0];
        x1 = x2 = p0.x();
        y1 = y2 = p0.y();
        for( int i = 1; i < m_pointList.size(); i++ ){
            QPoint p = m_pointList[i];
            if( p.x() < x1 ) x1 = p.x();
            if( p.y() < y1 ) y1 = p.y();
            if( x2 < p.x() ) x2 = p.x();
            if( y2 < p.y() ) y2 = p.y();
        }
    }
    return QRect(x1,y1,x2-x1,y2-y1).adjusted( - m_width, - m_width, m_width, m_width );
}

void FreeHand::shift(QPoint diff)
{
    for( int i = 0; i < m_pointList.size(); i++ ){
        m_pointList[i] += diff;
    }
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
