#include "freehand.h"
#include "rectangle.h"
#include "shape.h"
#include "shapewriter.h"

ShapeWriter::ShapeWriter(QDataStream &outStream)
    : m_outStream(outStream)
{

}

ShapeWriter::~ShapeWriter()
{

}

void ShapeWriter::handleShape( Shape *shape )
{
    m_outStream << shape->type();
    m_outStream << shape->color();
    m_outStream << shape->width();
}

void ShapeWriter::handleShape( FreeHand *shape  )
{
    handleShape( (Shape*)shape );
    QVector<QPoint> points = shape->points();
    m_outStream << points.size();
    foreach( QPoint point, points ){
        m_outStream << point;
    }
}

void ShapeWriter::handleShape( Rectangle *shape )
{
    handleShape( (Shape*)shape );
    m_outStream << shape->fillColor();
    m_outStream << shape->point1();
    m_outStream << shape->point2();
}
