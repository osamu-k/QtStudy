#ifndef CVOPENGLPROGRAM_H
#define CVOPENGLPROGRAM_H

#include <cvopenglfunctions.h>
#include <cvopenglvertexbuffer.h>

#include <QMatrix4x4>

#include <map>
#include <string>

class CVOpenGLShaderProgram
{
public:
    constexpr static const char * const c_uniformModelViewMatrix = "u_modelViewMatrix";
    constexpr static const char * const c_uniformProjectionMatrix = "u_projectionMatrix";

    constexpr static const char * const c_attribPosition = "a_position";
    constexpr static const char * const c_attribColor = "a_color";

    CVOpenGLShaderProgram();
    ~CVOpenGLShaderProgram();

    void create();
    void use();
    void setModelViewMatrix(const QMatrix4x4 &value);
    void setProjectionMatrix(const QMatrix4x4 &value);

    void fillPolygon(CVOpenGLVertexBuffer *vertexBuffer, GLint first, GLint count);

private:
    GLuint createShader(GLenum type, const char *name);
    std::string shaderSource(const char *name);

    CVOpenGLFunctions *m_gl;
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;
    GLuint m_program = 0;
};

#endif // CVOPENGLPROGRAM_H
