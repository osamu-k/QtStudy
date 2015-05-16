#include "imagepainter.h"

ImagePainter::ImagePainter()
{

}

ImagePainter::~ImagePainter()
{

}

void ImagePainter::draw(QPainter &painter, Image *image)
{
    painter.drawPixmap(QRect(image->position(),image->size()),image->pixmap());
}
