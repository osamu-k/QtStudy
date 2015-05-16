#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include "image.h"
#include "shapemanipulator.h"

class ImageManipulator : public ShapeManipulator
{
public:
    ImageManipulator();
    ~ImageManipulator();

    bool dragEnterEvent(QDragEnterEvent *);
    bool dragLeaveEvent(QDragLeaveEvent *);
    bool dragMoveEvent(QDragMoveEvent *);
    bool dropEvent(QDropEvent *);
    void draw(QPainter &painter);

private:
    void loadPixmap(QString filename,QPoint position);
    Image *m_image;
};

#endif // IMAGEMANIPULATOR_H
