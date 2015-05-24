#ifndef SHAPEWRITER_H
#define SHAPEWRITER_H

#include <QDataStream>
#include <shapehandler.h>

class ShapeWriter : public ShapeHandler
{
public:
    ShapeWriter(QDataStream &outStream);
    ~ShapeWriter();
    void handleShape( Shape * );
    void handleShape( FreeHand * );
    void handleShape( Rectangle * );
private:
    QDataStream  &m_outStream;
};

#endif // SHAPEWRITER_H
