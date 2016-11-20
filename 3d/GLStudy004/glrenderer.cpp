#include "glrenderer.h"

#include "common.h"
#include "glshaderprogram.h"

#include <QOpenGLContext>
#include <QSurface>

GLRenderer *GLRenderer::m_instance = nullptr;

GLRenderer *GLRenderer::instance()
{
    LOG_METHOD_CALLED;

    if( m_instance == nullptr ){
        m_instance = new GLRenderer;
        m_instance->create();
    }
    return m_instance;
}


GLRenderer::GLRenderer()
{
    LOG_METHOD_CALLED;

    initializeOpenGLFunctions();
}

GLRenderer::~GLRenderer()
{
    LOG_METHOD_CALLED;
}

void GLRenderer::create()
{
    LOG_METHOD_CALLED;

    m_program = new GLShaderProgram;
    m_program->create();
}

QSize GLRenderer::surfaceSize() const
{
    return QOpenGLContext::currentContext()->surface()->size();
}

GLShaderProgram *GLRenderer::getShaderProgram()
{
    LOG_METHOD_CALLED;

    return m_program;
}

void GLRenderer::setModelMatrix( const QMatrix4x4 value )
{
    LOG_METHOD_CALLED;

    m_modelMatrix = value;
}

void GLRenderer::setViewMatrix( const QMatrix4x4 value )
{
    LOG_METHOD_CALLED;

    m_viewMatrix = value;
}

void GLRenderer::setProjectionMatrix( const QMatrix4x4 value )
{
    LOG_METHOD_CALLED;

    m_projectionMatrix = value;
}

void GLRenderer::setEyePosition(const QVector3D &value)
{
    LOG_METHOD_CALLED;

    m_eyePosition = value;
}

void GLRenderer::setLightCount(int value)
{
    LOG_METHOD_CALLED;

    m_lightCount = value;
}

void GLRenderer::setLight(int lightId, const GlLight &value)
{
    LOG_METHOD_CALLED;

    m_light[lightId] = value;
}

void GLRenderer::setMaterial(const GlMaterial &value)
{
    LOG_METHOD_CALLED;

    m_material = value;
}

void GLRenderer::startRendering()
{
    LOG_METHOD_CALLED;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glClearColor(0.25, 0.5, 0.75, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::drawPolygon(
        GLShaderProgram *program,
        GLVertexBuffer *vertexBuffer,
        int first,
        int count )
{
    program->use();

    program->setModelMatrix(m_modelMatrix);
    program->setViewMatrix(m_viewMatrix);
    program->setProjectionMatrix(m_projectionMatrix);

    program->setEyePosition(m_eyePosition);
    program->setLightCount(m_lightCount);
    for( int i = 0;  i < m_lightCount; i++ ){
        program->setLight(i, m_light[i]);
    }
    program->setMaterial(m_material);

    program->drawPolygon(vertexBuffer,first,count);

    program->unuse();
}

