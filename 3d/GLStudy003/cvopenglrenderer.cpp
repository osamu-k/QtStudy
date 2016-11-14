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

    m_gl->glEnable(GL_DEPTH_TEST);
    m_gl->glDepthFunc(GL_LEQUAL);

    m_gl->glEnable(GL_CULL_FACE);
    m_gl->glFrontFace(GL_CCW);
    m_gl->glCullFace(GL_BACK);

    m_gl->glClearColor(0.25, 0.5, 0.75, 1.0);
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

void CVOpenGLRenderer::setModelViewMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    m_modelViewMatrix = value;
}

void CVOpenGLRenderer::setProjectionMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    m_projectionMatrix = value;
}

void CVOpenGLRenderer::useProgram(CVOpenGLShaderProgram *program)
{
    program->use();
    program->setModelViewMatrix(m_modelViewMatrix);
    program->setProjectionMatrix(m_projectionMatrix);
}
