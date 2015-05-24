#include "image.h"
#include "shapetypes.h"

Image::Image()
    : Shape(SHAPE_TYPE_IMAGE)
{

}

Image::~Image()
{

}

void Image::setPixmap(QPixmap pixmap)
{
    m_pixmap = pixmap;
    m_size = pixmap.size();
}

QPixmap Image::pixmap()
{
    return m_pixmap;
}

void Image::setPosition(QPoint position)
{
    m_position = position;
}

QPoint Image::position()
{
    return m_position;
}

void Image::setSize(QSize size)
{
    m_size = size;
}

QSize Image::size()
{
    return m_size;
}

//    void draw(QPainter &painter);

QRect Image::boundingRect()
{
    return QRect(m_position,m_size);
}

void Image::shift(QPoint diff)
{
    m_position += diff;
}

void Image::handle(ShapeHandler *handler)
{
    handler->handleShape(this);
}

void Image::writeTo( QDataStream &outStream )
{
    Shape::writeTo(outStream);
    outStream << m_position;
    outStream << m_size;
    outStream << m_pixmap;
}

void Image::readFrom( QDataStream &inStream )
{
    Shape::readFrom(inStream);
    inStream >> m_position;
    inStream >> m_size;
    inStream >> m_pixmap;
}
