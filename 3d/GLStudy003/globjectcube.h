#ifndef GLOBJECTCUBE_H
#define GLOBJECTCUBE_H

#include "globject.h"
#include "cvopenglvertexbuffer.h"

class GLObjectCube : public GLObject
{
public:
    GLObjectCube();
    ~GLObjectCube();

protected:
    void create();
    void draw();

private:
    CVOpenGLVertexBuffer *m_vertexBuffer;
};

#endif // GLOBJECTCUBE_H
