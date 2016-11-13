#include "common.h"
#include "cvopenglfunctions.h"

CVOpenGLFunctions *CVOpenGLFunctions::m_instance = nullptr;

CVOpenGLFunctions *CVOpenGLFunctions::instance()
{
    LOG_METHOD_CALLED;

    if( m_instance == nullptr ){
        m_instance = new CVOpenGLFunctions;
        m_instance->initializeOpenGLFunctions();
    }
    return m_instance;
}

CVOpenGLFunctions::CVOpenGLFunctions()
{
    LOG_METHOD_CALLED;
}
