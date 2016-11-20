#include "globjectcube.h"

#include "common.h"

#define NUM_FACES   6
#define NUM_VERTICE 4
#define STRIDE (sizeof(GLfloat) * (3+3+4))
#define BUFFER_SIZE (STRIDE * NUM_FACES * NUM_VERTICE)

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

    m_vertexBuffer = new GLVertexBuffer;
    m_vertexBuffer->create(BUFFER_SIZE);

    GLfloat *datap = reinterpret_cast<GLfloat*>(m_vertexBuffer->data());
    int idxPosition = 0;
    int idxColor = 0;
    for( int i = 0; i < NUM_FACES; i++ ){

        QVector3D p1( arrayPosition[idxPosition+0],
                      arrayPosition[idxPosition+1],
                      arrayPosition[idxPosition+2] );
        QVector3D p2( arrayPosition[idxPosition+3],
                      arrayPosition[idxPosition+4],
                      arrayPosition[idxPosition+5] );
        QVector3D p3( arrayPosition[idxPosition+6],
                      arrayPosition[idxPosition+7],
                      arrayPosition[idxPosition+8] );
        QVector3D normal = QVector3D::normal( p2 - p1, p3 - p2 );
        normal.normalize();

        for( int i = 0; i < NUM_VERTICE; i++ ){

            *(datap++) = arrayPosition[idxPosition++];
            *(datap++) = arrayPosition[idxPosition++];
            *(datap++) = arrayPosition[idxPosition++];

            *(datap++) = normal[0];
            *(datap++) = normal[1];
            *(datap++) = normal[2];

            *(datap++) = arrayColor[idxColor++];
            *(datap++) = arrayColor[idxColor++];
            *(datap++) = arrayColor[idxColor++];
            *(datap++) = arrayColor[idxColor++];
        }
    }

    m_vertexBuffer->store();

    m_vertexBuffer->setStride(STRIDE);
}

void GLObjectCube::draw()
{
    LOG_METHOD_CALLED;

    GLShaderProgram *program = m_renderer->getShaderProgram();

    for( int i = 0; i < 6; i++ ){
        int offset = STRIDE * 4 * i;
        m_vertexBuffer->setAttributeInfo(
                            GLShaderProgram::c_attribPosition,
                            3,
                            GL_FLOAT,
                            offset );
        m_vertexBuffer->setAttributeInfo(
                            GLShaderProgram::c_attribNormal,
                            3,
                            GL_FLOAT,
                            offset + sizeof(GLfloat)*3 );
        m_vertexBuffer->setAttributeInfo(
                            GLShaderProgram::c_attribColor,
                            4,
                            GL_FLOAT,
                            offset + sizeof(GLfloat)*(3+3) );
        m_renderer->drawPolygon(program,m_vertexBuffer,0,4);
    }
}
