#include "imagemanipulator.h"
#include "image.h"

// for Drag and Drop
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QPainter>
#include <QUrl>

ImageManipulator::ImageManipulator()
{

}

ImageManipulator::~ImageManipulator()
{

}

bool ImageManipulator::dragEnterEvent(QDragEnterEvent *event)
{
    foreach( QUrl url, event->mimeData()->urls() ){
        QString filename = url.toLocalFile();
        QString suffix = QFileInfo(filename).suffix().toLower();
        if((suffix=="png")||(suffix=="jpg")||(suffix=="jpeg")){
            event->acceptProposedAction();
            loadPixmap(filename,event->pos());
            QRegion region(QRect(m_image->position(),m_image->size()));
            emit updateRegion(region);
            return true;
        }
    }
    return false;
}

bool ImageManipulator::dragLeaveEvent(QDragLeaveEvent *)
{
    if( m_image ){
        QRegion region(QRect(m_image->position(),m_image->size()));
        emit updateRegion(region);

        delete m_image;
        m_image = 0;
        return true;
    }
    return false;
}

bool ImageManipulator::dragMoveEvent(QDragMoveEvent *event)
{
    foreach( QUrl url, event->mimeData()->urls() ){
        QString filename = url.toLocalFile();
        QString suffix = QFileInfo(filename).suffix().toLower();
        if((suffix=="png")||(suffix=="jpg")||(suffix=="jpeg")){
            event->acceptProposedAction();
            QRegion region(QRect(m_image->position(),m_image->size()));
            m_image->setPosition(event->pos());
            region = region.united(QRect(m_image->position(),m_image->size()));
            emit updateRegion(region);
            return true;
        }
    }
    return false;
}

bool ImageManipulator::dropEvent(QDropEvent *event)
{
    foreach(QUrl url,event->mimeData()->urls()){
        QString filename = url.toLocalFile();
        QString suffix = QFileInfo(filename).suffix().toLower();
        if((suffix=="png")||(suffix=="jpg")||(suffix=="jpeg")){
            event->acceptProposedAction();

            QRegion region(QRect(m_image->position(),m_image->size()));
            m_image->setPosition(event->pos());
            emit updateRegion(region);

            emit newShape(m_image);
            m_image = 0;
            return true;
        }
    }
    return false;
}

void ImageManipulator::loadPixmap(QString filename, QPoint position)
{
    QPixmap pixmap(filename);
    m_image = new Image();
    m_image->setPixmap(pixmap);
    m_image->setPosition(position);
}

void ImageManipulator::draw(QPainter &painter)
{
    if( m_image ){
        painter.save();
        painter.setOpacity(0.5);
        painter.drawPixmap(QRect(m_image->position(),m_image->size()),m_image->pixmap());
        painter.restore();
    }
}
