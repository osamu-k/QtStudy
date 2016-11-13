#include "cvopenglvertexbuffer.h"

#include <QDebug>

CVOpenGLVertexBuffer::CVOpenGLVertexBuffer()
{
    m_gl = CVOpenGLFunctions::instance();
}

void CVOpenGLVertexBuffer::create(GLsizeiptr size)
{
    m_gl->glGenBuffers(1,&m_buffer);
    m_size = size;
}

GLuint CVOpenGLVertexBuffer::name() const
{
    return m_buffer;
}

void *CVOpenGLVertexBuffer::data()
{
    if( m_data == nullptr ){
        m_data = new unsigned char[m_size];
    }
    return m_data;
}

void CVOpenGLVertexBuffer::store()
{
    m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    m_gl->glBufferData(GL_ARRAY_BUFFER,
                       m_size,
                       reinterpret_cast<void *>(m_data),
                       GL_STATIC_DRAW);
    delete[] m_data;
    m_data = nullptr;
}

void CVOpenGLVertexBuffer::setStride(GLsizei stride)
{
    m_stride = stride;
}

GLsizei CVOpenGLVertexBuffer::stride() const
{
    return m_stride;
}

void CVOpenGLVertexBuffer::setAttributeInfo(const char *name, GLint size, GLenum type, GLint offset)
{
    AttributeInfo info;
    info.size = size;
    info.type = type;
    info.offset = offset;
    m_attributeMap[name] = info;
}

const std::map<std::string,CVOpenGLVertexBuffer::AttributeInfo> &CVOpenGLVertexBuffer::attributeMap() const
{
    return m_attributeMap;
}

void CVOpenGLVertexBuffer::bind()
{
    m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}
