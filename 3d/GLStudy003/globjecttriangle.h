#ifndef GLOBJECTTRIANGLE_H
#define GLOBJECTTRIANGLE_H

#include "globject.h"
#include "cvopenglvertexbuffer.h"

class GLObjectTriangle : public GLObject
{
public:
    GLObjectTriangle();
    ~GLObjectTriangle();

protected:
    void create();
    void draw();

private:
    CVOpenGLVertexBuffer *m_vertexBuffer;
};

#endif // GLOBJECTTRIANGLE_H
