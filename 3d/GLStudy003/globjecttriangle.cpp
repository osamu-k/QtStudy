#include "common.h"
#include "globjecttriangle.h"
#include "cvopenglrenderer.h"

static GLfloat arrayPosition[] = {
     0.0,  1.0,  0.0,
    -1.0, -1.0,  0.0,
     1.0, -1.0,  0.0,
};

static GLfloat arrayColor[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
};

GLObjectTriangle::GLObjectTriangle()
    : GLObject()
{
    LOG_METHOD_CALLED;
}

GLObjectTriangle::~GLObjectTriangle()
{
    LOG_METHOD_CALLED;
}

void GLObjectTriangle::create()
{
    LOG_METHOD_CALLED;

    m_vertexBuffer = new CVOpenGLVertexBuffer;
    m_vertexBuffer->create(sizeof(GLfloat)*3*(3+4));

    GLfloat *datap = reinterpret_cast<GLfloat*>(m_vertexBuffer->data());
    int idxPosition = 0;
    int idxColor = 0;
    for( int i = 0; i < 3; i++ ){
        *(datap++) = arrayPosition[idxPosition++];
        *(datap++) = arrayPosition[idxPosition++];
        *(datap++) = arrayPosition[idxPosition++];

        *(datap++) = arrayColor[idxColor++];
        *(datap++) = arrayColor[idxColor++];
        *(datap++) = arrayColor[idxColor++];
        *(datap++) = arrayColor[idxColor++];
    }

    m_vertexBuffer->store();

    m_vertexBuffer->setStride(sizeof(GLfloat)*(3+4));
    m_vertexBuffer->setAttributeInfo("a_position",3,GL_FLOAT,0);
    m_vertexBuffer->setAttributeInfo("a_color",4,GL_FLOAT,sizeof(GLfloat)*3);
}

void GLObjectTriangle::draw()
{
    LOG_METHOD_CALLED;

    CVOpenGLShaderProgram *program = m_renderer->getShaderProgram(CVOpenGLRenderer::CommonShader);
    m_renderer->useProgram(program);
    program->fillPolygon(m_vertexBuffer,0,3);
}
