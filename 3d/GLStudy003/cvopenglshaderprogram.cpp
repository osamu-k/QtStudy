#include "cvopenglshaderprogram.h"

#include "common.h"
#include "cvopenglrenderer.h"
#include "cvopenglshaderprogram.h"

#include <QFile>
#include <QMatrix4x4>

CVOpenGLShaderProgram::CVOpenGLShaderProgram()
{
    LOG_METHOD_CALLED;

    m_gl = CVOpenGLFunctions::instance();
}

CVOpenGLShaderProgram::~CVOpenGLShaderProgram()
{
    LOG_METHOD_CALLED;
}

void CVOpenGLShaderProgram::create()
{
    LOG_METHOD_CALLED;

    m_vertexShader = createShader(GL_VERTEX_SHADER,"vertexshader01.vsh");
    if( m_vertexShader == 0){
        return;
    }
    m_fragmentShader = createShader(GL_FRAGMENT_SHADER,"fragmentshader01.fsh");
    if( m_fragmentShader == 0 ){
        m_gl->glDeleteShader(m_vertexShader);
        return;
    }

    m_program = m_gl->glCreateProgram();
    if( m_program == 0 ){
        m_gl->glDeleteShader(m_vertexShader);
        m_gl->glDeleteShader(m_fragmentShader);
    }

    m_gl->glAttachShader(m_program, m_vertexShader);
    m_gl->glAttachShader(m_program, m_fragmentShader);
    m_gl->glLinkProgram(m_program);

    GLint uniformCount = 0;
    m_gl->glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);
    qDebug() << "uniformCount = " << uniformCount;

    GLint uniformNameMax = 0;
    m_gl->glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameMax);
    qDebug() << "uniformNameMax = " << uniformNameMax;

    for( int i = 0; i < uniformCount; i++ ){
        char name[uniformNameMax+1];
        GLint size;
        GLenum type;
        m_gl->glGetActiveUniform( m_program, i, uniformNameMax, 0, &size, &type, name );
        qDebug() << "uniform name = " << name << ", type = " << type << ", size = " << size;
    }

    GLint attributeCount = 0;
    m_gl->glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attributeCount);
    qDebug() << "attributeCount = " << uniformCount;

    GLint attributeNameMax = 0;
    m_gl->glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeNameMax);
    qDebug() << "attributeNameMax = " << attributeNameMax;

    for( int i = 0; i < attributeCount; i++ ){
        char name[attributeNameMax+1];
        GLint size;
        GLenum type;
        m_gl->glGetActiveAttrib(m_program, i, attributeNameMax, 0, &size, &type, name );
        qDebug() << "attribute name = " << name << ", type = " << type << ", size = " << size;
    }
}

GLuint CVOpenGLShaderProgram::createShader(GLenum type, const char *name)
{
    LOG_METHOD_CALLED;

    GLuint shader = m_gl->glCreateShader(type);
    std::string source = shaderSource(name);
    const char *sourcep = source.c_str();
    m_gl->glShaderSource(shader, 1, &sourcep, 0);
    m_gl->glCompileShader(shader);
    return shader;
}

std::string CVOpenGLShaderProgram::shaderSource(const char *name)
{
    LOG_METHOD_CALLED;

    QString filename = QString(":/").append(name);
    qDebug() << "filename = " << filename;
    QFile file(filename);
    if( ! file.open(QIODevice::ReadOnly) ){
        qDebug() <<"file open error !";
        return std::string();
    }

    return file.readAll().toStdString();
}

void CVOpenGLShaderProgram::use()
{
    LOG_METHOD_CALLED;

    m_gl->glUseProgram(m_program);
}

void CVOpenGLShaderProgram::setModelViewMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    GLint location = m_gl->glGetUniformLocation(m_program,c_uniformModelViewMatrix);
    qDebug() << "location = " << location;
    qDebug() << "value = " << value;
    if( location >= 0 ){
        m_gl->glUniformMatrix4fv(location,1,GL_FALSE,value.constData());
    }
}

void CVOpenGLShaderProgram::setProjectionMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    GLint location = m_gl->glGetUniformLocation(m_program,c_uniformProjectionMatrix);
    if( location >= 0 ){
        m_gl->glUniformMatrix4fv(location,1,GL_FALSE,value.constData());
    }
}

void CVOpenGLShaderProgram::fillPolygon(CVOpenGLVertexBuffer *vertexBuffer, GLint first, GLint count)
{
    LOG_METHOD_CALLED;

    vertexBuffer->bind();

    GLsizei stride = vertexBuffer->stride();
    qDebug() << "stride = " << stride;
    for( auto attribInfo : vertexBuffer->attributeMap() ){
        const std::string &name = attribInfo.first;
        const CVOpenGLVertexBuffer::AttributeInfo &info = attribInfo.second;
        GLint index = m_gl->glGetAttribLocation(m_program, name.c_str());

        qDebug() << "index = " << index
                 << ", name = " << name.c_str()
                 << ", size = " << info.size
                 << ", type = " << info.type
                 << ", offset = " << info.offset;

        m_gl->glEnableVertexAttribArray(index);
        m_gl->glVertexAttribPointer(
                    index,
                    info.size,
                    info.type,
                    GL_FALSE,
                    stride,
                    reinterpret_cast<const void *>(info.offset)
              );
    }

    m_gl->glDrawArrays(GL_TRIANGLE_FAN,first,count);

    for( auto attribInfo : vertexBuffer->attributeMap() ){
        const std::string &name = attribInfo.first;
        GLint index = m_gl->glGetAttribLocation(m_program, name.c_str());
        m_gl->glDisableVertexAttribArray(index);
    }
}
