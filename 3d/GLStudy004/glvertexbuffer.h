#ifndef GLVERTEXBUFFER_H
#define GLVERTEXBUFFER_H

#include <QOpenGLFunctions>
#include <QString>

class GLVertexBuffer : QOpenGLFunctions
{
public:
    GLVertexBuffer();
    ~GLVertexBuffer();

    void create(int size);

    void *data();
    void store();

    void setStride(int stride);
    int stride() const;

    void setAttributeInfo(const char *name, int size, GLenum type, int offset);
    struct AttributeInfo{
        int size;
        GLenum type;
        int offset;
    };
    const std::map<QString,GLVertexBuffer::AttributeInfo> &attributeMap() const;

    void bind();
    void unbind();

private:
    GLuint m_buffer = 0;
    int m_size = 0;
    void *m_data = nullptr;
    int m_stride = 0;
    std::map<QString,GLVertexBuffer::AttributeInfo> m_attributeMap;
};

#endif // GLVERTEXBUFFER_H
