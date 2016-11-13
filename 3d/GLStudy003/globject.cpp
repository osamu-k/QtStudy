#include "common.h"
#include "globject.h"

GLObject::GLObject()
{
    LOG_METHOD_CALLED;

    m_gl = CVOpenGLFunctions::instance();
    m_renderer = CVOpenGLRenderer::instance();
}

GLObject::~GLObject()
{
    LOG_METHOD_CALLED;
}
