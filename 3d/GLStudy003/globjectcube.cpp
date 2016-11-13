#include "common.h"
#include "globjectcube.h"

#define NUM_FACES   6
#define NUM_VERTICE 4

static GLfloat arrayPosition[] =
{
    // front
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,

    // right
     0.5,  0.5, -0.5,
     0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5, -0.5, -0.5,

    // back
    -0.5,  0.5, -0.5,
     0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,

    // left
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,

    // top
     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,

    // bottom
     0.5, -0.5,  0.5,
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
};

static GLfloat arrayColor[] =
{
    // front
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,

    // right
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,

    // back
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,

    // left
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,

    // top
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,

    // bottom
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
};

GLObjectCube::GLObjectCube()
{

}

GLObjectCube::~GLObjectCube()
{

}

void GLObjectCube::create()
{
    LOG_METHOD_CALLED;

    m_vertexBuffer = new CVOpenGLVertexBuffer;
    m_vertexBuffer->create(sizeof(GLfloat)*4*6*(3+4));

    GLfloat *datap = reinterpret_cast<GLfloat*>(m_vertexBuffer->data());
    int idxPosition = 0;
    int idxColor = 0;
    for( int i = 0; i < 4*6; i++ ){
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
//    m_vertexBuffer->setAttributeInfo("a_position",3,GL_FLOAT,0);
//    m_vertexBuffer->setAttributeInfo("a_color",4,GL_FLOAT,sizeof(GLfloat)*3);
}

void GLObjectCube::draw()
{
    LOG_METHOD_CALLED;

    CVOpenGLShaderProgram *program = m_renderer->getShaderProgram(CVOpenGLRenderer::CommonShader);
    m_renderer->useProgram(program);

    for( int i = 0; i < 6; i++ ){
        m_vertexBuffer->setAttributeInfo("a_position",3,GL_FLOAT,
                                         sizeof(GLfloat)*4*(3+4)*i );
        m_vertexBuffer->setAttributeInfo("a_color",4,GL_FLOAT,
                                         sizeof(GLfloat)*4*(3+4)*i + sizeof(GLfloat)*3);
        program->fillPolygon(m_vertexBuffer,0,4);
    }
}
