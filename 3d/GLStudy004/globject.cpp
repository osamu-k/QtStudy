#include "globject.h"

#include "common.h"

GLObject::GLObject()
{
    LOG_METHOD_CALLED;

    initializeOpenGLFunctions();
    m_renderer = GLRenderer::instance();
}

GLObject::~GLObject()
{
    LOG_METHOD_CALLED;
}
