#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "cvopenglfunctions.h"
#include "cvopenglrenderer.h"

class GLObject
{
public:
    GLObject();
    virtual ~GLObject();

    virtual void create() = 0;
    virtual void draw() = 0;

protected:
    CVOpenGLFunctions *m_gl;
    CVOpenGLRenderer *m_renderer;
};

#endif // GLOBJECT_H
