#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "glrenderer.h"

#include <QOpenGLFunctions>

class GLObject : public QOpenGLFunctions
{
public:
    GLObject();
    virtual ~GLObject();

    virtual void create() = 0;
    virtual void draw() = 0;

protected:
    GLRenderer *m_renderer;
};

#endif // GLOBJECT_H
