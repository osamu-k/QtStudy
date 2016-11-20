#include "glvertexbuffer.h"

#include "common.h"

GLVertexBuffer::GLVertexBuffer()
{
    LOG_METHOD_CALLED;

    initializeOpenGLFunctions();
}

GLVertexBuffer::~GLVertexBuffer()
{
    LOG_METHOD_CALLED;
}

void GLVertexBuffer::create(int size)
{
    LOG_METHOD_CALLED;

    glGenBuffers(1,&m_buffer);
    m_size = size;
}

void *GLVertexBuffer::data()
{
    LOG_METHOD_CALLED;

    if( m_data == nullptr ){
        m_data = new unsigned char[m_size];
    }
    return m_data;
}

void GLVertexBuffer::store()
{
    LOG_METHOD_CALLED;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,
                       m_size,
                       reinterpret_cast<void *>(m_data),
                       GL_STATIC_DRAW);
    delete[] m_data;
    m_data = nullptr;
}

void GLVertexBuffer::setStride(int stride)
{
    LOG_METHOD_CALLED;

    m_stride = stride;
}

GLsizei GLVertexBuffer::stride() const
{
    LOG_METHOD_CALLED;

    return m_stride;
}

void GLVertexBuffer::setAttributeInfo(const char *name, int size, GLenum type, int offset)
{
    LOG_METHOD_CALLED;

    AttributeInfo info;
    info.size = size;
    info.type = type;
    info.offset = offset;
    m_attributeMap[name] = info;
}

const std::map<QString,GLVertexBuffer::AttributeInfo> &GLVertexBuffer::attributeMap() const
{
    LOG_METHOD_CALLED;

    return m_attributeMap;
}

void GLVertexBuffer::bind()
{
    LOG_METHOD_CALLED;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void GLVertexBuffer::unbind()
{
    LOG_METHOD_CALLED;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
