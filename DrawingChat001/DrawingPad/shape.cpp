#include "shape.h"
#include <QDebug>
#include <QDateTime>

Shape::Shape(int type)
    : m_id(0)
    , m_type(type)
    , m_color(Qt::black)
    , m_width(0)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    m_id = dateTime.toMSecsSinceEpoch();
    qDebug() << "dateTime.toMSecsSinceEpoch() = " << dateTime.toMSecsSinceEpoch();
}

Shape::~Shape()
{
}

void Shape::setId(qint64 id)
{
    m_id = id;
}

qint64 Shape::id()
{
    return m_id;
}

int Shape::type()
{
    return m_type;
}

void Shape::setColor(QColor color)
{
    m_color = color;
}

void Shape::setWidth(int width)
{
    m_width = width;
}

QColor Shape::color()
{
    return m_color;
}

int Shape::width()
{
    return m_width;
}

bool Shape::hitTest(QPoint pos)
{
    QRect rect = boundingRect();
    int d = m_width / 2;
    rect.adjust( -d, -d, d, d );
    return rect.contains(pos);
}

void Shape::writeTo( QDataStream &outStream )
{
    outStream << m_type;
    outStream << m_id;
    outStream << m_color;
    outStream << m_width;
}

void Shape::readFrom( QDataStream &inStream )
{
    inStream >> m_id;
    inStream >> m_color;
    inStream >> m_width;
}
