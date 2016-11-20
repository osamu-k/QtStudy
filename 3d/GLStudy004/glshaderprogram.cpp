#include "glshaderprogram.h"

#include "common.h"
#include "glvertexbuffer.h"

#include <QFile>

GLShaderProgram::GLShaderProgram()
{
    LOG_METHOD_CALLED;

    initializeOpenGLFunctions();
}

GLShaderProgram::~GLShaderProgram()
{
    LOG_METHOD_CALLED;

    if( m_program ){
        glDeleteProgram( m_program );
        m_program = 0;
    }
    if( m_vertexShader ){
        glDeleteShader( m_vertexShader );
        m_vertexShader = 0;
    }
    if( m_fragmentShader ){
        glDeleteShader( m_fragmentShader );
        m_fragmentShader = 0;
    }
}

void GLShaderProgram::create()
{
    LOG_METHOD_CALLED;

    m_vertexShader = createShader(GL_VERTEX_SHADER,"fragmentlighting.vsh");
    if( m_vertexShader == 0){
        return;
    }
    m_fragmentShader = createShader(GL_FRAGMENT_SHADER,"fragmentlighting2.fsh");
    if( m_fragmentShader == 0 ){
        glDeleteShader(m_vertexShader);
        return;
    }
    m_program = glCreateProgram();
    if( m_program == 0 ){
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);
        return;
    }

    if( ! linkProgram() ){
        glDeleteProgram(m_program);
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);
        return;
    }

    GLint uniformCount = 0;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);
    qDebug() << "uniformCount = " << uniformCount;

    GLint uniformNameMax = 0;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameMax);
    qDebug() << "uniformNameMax = " << uniformNameMax;

    for( int i = 0; i < uniformCount; i++ ){
        char name[uniformNameMax+1];
        GLint size;
        GLenum type;
        glGetActiveUniform( m_program, i, uniformNameMax, 0, &size, &type, name );
        qDebug() << "uniform name = " << name << ", type = " << type << ", size = " << size;
    }

    GLint attributeCount = 0;
    glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attributeCount);
    qDebug() << "attributeCount = " << uniformCount;

    GLint attributeNameMax = 0;
    glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeNameMax);
    qDebug() << "attributeNameMax = " << attributeNameMax;

    for( int i = 0; i < attributeCount; i++ ){
        char name[attributeNameMax+1];
        GLint size;
        GLenum type;
        glGetActiveAttrib(m_program, i, attributeNameMax, 0, &size, &type, name );
        qDebug() << "attribute name = " << name << ", type = " << type << ", size = " << size;
    }
}

GLuint GLShaderProgram::createShader(GLenum type, const char *name)
{
    LOG_METHOD_CALLED;

    GLuint shader = glCreateShader(type);
    std::string source = shaderSource(name);
    const char *sourcep = source.c_str();
    glShaderSource(shader, 1, &sourcep, 0);
    glCompileShader(shader);

    GLint compiled = false;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if( ! compiled ){
        qDebug() << "Compile failed !";
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if( infoLen > 0 ){
            char *infoLog = new char[infoLen + 1];
            glGetProgramInfoLog(m_program, infoLen+1, NULL, infoLog );
            qDebug() << QString(infoLog);
            delete[] infoLog;
            return 0;
        }
    }

    return shader;
}

std::string GLShaderProgram::shaderSource(const char *name)
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

bool GLShaderProgram::linkProgram()
{
    LOG_METHOD_CALLED;

    glAttachShader(m_program, m_vertexShader);
    glAttachShader(m_program, m_fragmentShader);
    glLinkProgram(m_program);

    GLint linked = false;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
    if( ! linked ){
        qDebug() << "Link failed !";
        GLint infoLen = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLen);
        if( infoLen > 0 ){
            char *infoLog = new char[infoLen + 1];
            glGetProgramInfoLog(m_program, infoLen+1, NULL, infoLog );
            qDebug() << QString(infoLog);
            delete[] infoLog;
            return false;
        }
    }
    return true;
}

void GLShaderProgram::use()
{
    LOG_METHOD_CALLED;

    glUseProgram(m_program);
}

void GLShaderProgram::unuse()
{
    LOG_METHOD_CALLED;

    glUseProgram(0);
}

void GLShaderProgram::setModelMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformModelMatrix,value);

    QMatrix4x4 uniformMatrix = value.inverted().transposed();
    setUniform(c_uniformNormalMatrix,uniformMatrix);
}

void GLShaderProgram::setViewMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformViewMatrix,value);
}

void GLShaderProgram::setProjectionMatrix(const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformProjectionMatrix,value);
}

void GLShaderProgram::setEyePosition(const QVector3D &value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformEyePosition,value);
}

void GLShaderProgram::setLightCount(int value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformLightCount,value);
}

void GLShaderProgram::setLight(int lightId, const GlLight &value)
{
    LOG_METHOD_CALLED;

    QString name;

    name = QString(c_uniformLightPosition).arg(lightId);
    setUniform(name.toLatin1().constData(),value.position);

    name = QString(c_uniformLightAmbient).arg(lightId);
    setUniform(name.toLatin1().constData(),value.ambient);

    name = QString(c_uniformLightDiffuse).arg(lightId);
    setUniform(name.toLatin1().constData(),value.diffuse);

    name = QString(c_uniformLightSpecular).arg(lightId);
    setUniform(name.toLatin1().constData(),value.specular);

    name = QString(c_uniformLightSpotEnabled).arg(lightId);
    setUniform(name.toLatin1().constData(),value.spotEnabled);

    name = QString(c_uniformLightSpotDirection).arg(lightId);
    setUniform(name.toLatin1().constData(),value.spotDirection);

    name = QString(c_uniformLightSpotCutOff).arg(lightId);
    setUniform(name.toLatin1().constData(),value.spotCutOff);

    name = QString(c_uniformLightSpotExponent).arg(lightId);
    setUniform(name.toLatin1().constData(),value.spotExponent);

    name = QString(c_uniformLightAttenuationEnabled).arg(lightId);
    setUniform(name.toLatin1().constData(),value.attenuationEnabled);

    name = QString(c_uniformLightAttenuationFactor).arg(lightId);
    setUniform(name.toLatin1().constData(),value.attenuationFactor);
}

void GLShaderProgram::setMaterial(const GlMaterial &value)
{
    LOG_METHOD_CALLED;

    setUniform(c_uniformMaterialSpecular,value.specular);
    setUniform(c_uniformMaterialShininess,value.shininess);
}

void GLShaderProgram::setUniform(const char *name, int value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniform1i(location, value);
    }
}

void GLShaderProgram::setUniform(const char *name, bool value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniform1i(location, (value ? 1 : 0));
    }
}

void GLShaderProgram::setUniform(const char *name, float value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniform1f(location, value);
    }
}

void GLShaderProgram::setUniform(const char *name, const QVector3D &value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniform3f(location,value[0],value[1],value[2]);
    }
}

void GLShaderProgram::setUniform(const char *name, const QVector4D &value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniform4f(location,value[0],value[1],value[2],value[3]);
    }
}

void GLShaderProgram::setUniform(const char *name, const QMatrix4x4 &value)
{
    LOG_METHOD_CALLED;

    GLint location = glGetUniformLocation(m_program,name);
    qDebug() << "name=" << name << " location=" << location << " value=" << value;
    if( location >= 0 ){
        glUniformMatrix4fv(location,1,GL_FALSE,value.constData());
    }
}

void GLShaderProgram::drawPolygon(GLVertexBuffer *vertexBuffer, int first, int count)
{
    LOG_METHOD_CALLED;

    setupVertexAttributes(vertexBuffer);

    glDrawArrays(GL_TRIANGLE_FAN,first,count);

    resetVertexAttributes(vertexBuffer);
}

void GLShaderProgram::setupVertexAttributes(GLVertexBuffer *vertexBuffer)
{
    LOG_METHOD_CALLED;

    vertexBuffer->bind();

    GLsizei stride = vertexBuffer->stride();
    qDebug() << "stride = " << stride;
    for( auto attribInfo : vertexBuffer->attributeMap() ){
        const QString &name = attribInfo.first;
        const GLVertexBuffer::AttributeInfo &info = attribInfo.second;
        GLint index = glGetAttribLocation(m_program, name.toLatin1().constData());

        qDebug() << "index = " << index
                 << ", name = " << name
                 << ", size = " << info.size
                 << ", type = " << info.type
                 << ", offset = " << info.offset;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
                    index,
                    info.size,
                    info.type,
                    GL_FALSE,
                    stride,
                    reinterpret_cast<const void *>(info.offset)
              );
    }
}

void GLShaderProgram::resetVertexAttributes(GLVertexBuffer *vertexBuffer)
{
    LOG_METHOD_CALLED;

    for( auto attribInfo : vertexBuffer->attributeMap() ){
        const QString &name = attribInfo.first;
        GLint index = glGetAttribLocation(m_program, name.toLatin1().constData());
        glDisableVertexAttribArray(index);
    }

    vertexBuffer->unbind();
}
