/**
canvas.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , m_lineColor( Qt::black )
    , m_lineWidth( 1 )
    , m_polyLine( 0 )
{
    setAutoFillBackground( true );
    setPalette( Qt::white );
}

Canvas::~Canvas()
{
    clearLineList();
}

void Canvas::setLineColor( QColor color )
{
    m_lineColor = color;
}

void Canvas::setLineWidth( int width )
{
    m_lineWidth = width;
}

void Canvas::clear()
{
    clearLineList();
    update();
}

void Canvas::clearLineList()
{
    foreach( PolyLine *polyLine, m_polyLineList ){
        delete polyLine;
    }
    m_polyLineList.clear();
}

void Canvas::writeTo( QDataStream &out ) const
{
    out << m_polyLineList.size();
    foreach( PolyLine *polyLine, m_polyLineList ){
        out << *polyLine;
    }
}

void Canvas::readFrom( QDataStream &in )
{
    int nLines = 0;
    in >> nLines;
    clearLineList();
    for( int i = 0; i < nLines; i++ ){
        PolyLine *polyLine = new PolyLine;
        in >> *polyLine;
        m_polyLineList << polyLine;
    }
    update();
}

void Canvas::addData( QByteArray data )
{
    qDebug() << "Adding data...";

    QDataStream in( &data, QIODevice::ReadOnly );
    PolyLine *polyLine = new PolyLine;
    in >> *polyLine;
    m_polyLineList << polyLine;
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    foreach( PolyLine *polyLine, m_polyLineList ){
        polyLine->draw( painter );
    }
    if( m_polyLine ){
        m_polyLine->draw( painter );
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton ){
        m_polyLine = new PolyLine;
        m_polyLine->addPoint( event->pos() );
        m_polyLine->setLineColor( m_lineColor );
        m_polyLine->setLineWidth( m_lineWidth );
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton ){
        if( m_polyLine ){
            m_polyLine->addPoint( event->pos() );
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton ){
        if( m_polyLine ){
            m_polyLine->addPoint( event->pos() );
            m_polyLineList << m_polyLine;

            QByteArray byteArray;
            QDataStream out( &byteArray, QIODevice::WriteOnly );
            out << *m_polyLine;
            emit dataAdded( byteArray );

            m_polyLine = 0;
            update();
        }
    }
}
