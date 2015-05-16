#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H

#include <QPainter>
#include "image.h"

class ImagePainter
{
public:
    ImagePainter();
    ~ImagePainter();
    void draw(QPainter &painter, Image *image);
};

#endif // IMAGEPAINTER_H
