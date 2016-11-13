#ifndef CVOPENGLVERTEXBUFFER_H
#define CVOPENGLVERTEXBUFFER_H

#include "cvopenglfunctions.h"

class CVOpenGLVertexBuffer
{
public:
    CVOpenGLVertexBuffer();

    void create(GLsizeiptr size);
    GLuint name() const;

    void *data();
    void store();

    void setStride(GLsizei stride);
    GLsizei stride() const;

    void setAttributeInfo(const char *name, GLint size, GLenum type, GLint offset);
    struct AttributeInfo{
        GLint size;
        GLenum type;
        GLint offset;
    };
    const std::map<std::string,CVOpenGLVertexBuffer::AttributeInfo> &attributeMap() const;

    void bind();

private:
    CVOpenGLFunctions *m_gl = nullptr;
    GLuint m_buffer = 0;
    GLsizeiptr m_size = 0;
    void *m_data = nullptr;
    GLsizei m_stride = 0;
    std::map<std::string,CVOpenGLVertexBuffer::AttributeInfo> m_attributeMap;
};

#endif // CVOPENGLVERTEXBUFFER_H
