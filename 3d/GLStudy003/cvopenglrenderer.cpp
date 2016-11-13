#include "common.h"
#include "cvopenglrenderer.h"

CVOpenGLRenderer *CVOpenGLRenderer::m_instance = nullptr;

CVOpenGLRenderer *CVOpenGLRenderer::instance()
{
    LOG_METHOD_CALLED;

    if( m_instance == nullptr ){
        m_instance = new CVOpenGLRenderer;
    }
    return m_instance;
}

CVOpenGLRenderer::CVOpenGLRenderer()
{
    LOG_METHOD_CALLED;

    m_gl = CVOpenGLFunctions::instance();
}

CVOpenGLRenderer::~CVOpenGLRenderer()
{
    LOG_METHOD_CALLED;
}

void CVOpenGLRenderer::startRendering()
{
    LOG_METHOD_CALLED;

    m_gl->glClearColor(1.0, 0.5, 0.25, 1.0);
    m_gl->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CVOpenGLRenderer::finishRendering()
{
    LOG_METHOD_CALLED;
}

CVOpenGLShaderProgram *CVOpenGLRenderer::getShaderProgram(ShaderProgramId id)
{
    LOG_METHOD_CALLED;

    if( m_shaderMap.find(id) == m_shaderMap.end() ){
        CVOpenGLShaderProgram *program = new CVOpenGLShaderProgram;
        program->create();
        m_shaderMap[id] = program;
    }
    return m_shaderMap[id];
}

void CVOpenGLRenderer::setModelMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    m_modelMatrix = value;
}

void CVOpenGLRenderer::setViewMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    m_viewMatrix = value;
}

void CVOpenGLRenderer::setProjectionMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    m_projectionMatrix = value;
}

void CVOpenGLRenderer::useProgram(CVOpenGLShaderProgram *program)
{
    program->use();
    program->setModelMatrix(m_modelMatrix);
    program->setViewMatrix(m_viewMatrix);
    program->setProjectionMatrix(m_projectionMatrix);
}
