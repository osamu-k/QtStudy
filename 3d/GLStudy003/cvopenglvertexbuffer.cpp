#include "cvopenglvertexbuffer.h"

#include <QDebug>

CVOpenGLVertexBuffer::CVOpenGLVertexBuffer()
{
    m_gl = CVOpenGLFunctions::instance();
}

void CVOpenGLVertexBuffer::create(GLsizeiptr size)
{
    m_gl->glGenBuffers(1,&m_buffer);
    m_data.resize(size);
}

GLuint CVOpenGLVertexBuffer::name() const
{
    return m_buffer;
}

void *CVOpenGLVertexBuffer::data()
{
    return reinterpret_cast<void *>(m_data.data());
}

void CVOpenGLVertexBuffer::update()
{
    m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    m_gl->glBufferData(GL_ARRAY_BUFFER,
                       m_data.size(),
                       reinterpret_cast<void *>(m_data.data()),
                       GL_STATIC_DRAW);
    qDebug() << "size = " << m_data.size();
    GLfloat *fp = reinterpret_cast<float *>(m_data.data());
    for( int i = 0; i < m_data.size() / sizeof(GLfloat); i++ ){
        qDebug() << "data[" << i << "] = " << *(fp++);
    }
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
