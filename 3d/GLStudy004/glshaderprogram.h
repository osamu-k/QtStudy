#ifndef GLSHADERPROGRAM_H
#define GLSHADERPROGRAM_H

#include "glcommon.h"

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector4D>

class GLVertexBuffer;

class GLShaderProgram : public QOpenGLFunctions
{
public:
    constexpr static const char * const c_uniformModelMatrix = "u_modelMatrix";
    constexpr static const char * const c_uniformViewMatrix = "u_viewMatrix";
    constexpr static const char * const c_uniformProjectionMatrix = "u_projectionMatrix";
    constexpr static const char * const c_uniformNormalMatrix = "u_normalMatrix";
    constexpr static const char * const c_uniformEyePosition = "u_eyePosition";
    constexpr static const char * const c_uniformLightCount = "u_lightCount";
    constexpr static const char * const c_uniformLightPosition = "u_light[%1].position";
    constexpr static const char * const c_uniformLightAmbient = "u_light[%1].ambient";
    constexpr static const char * const c_uniformLightDiffuse = "u_light[%1].diffuse";
    constexpr static const char * const c_uniformLightSpecular = "u_light[%1].specular";
    constexpr static const char * const c_uniformLightSpotEnabled = "u_light[%1].spotEnabled";
    constexpr static const char * const c_uniformLightSpotDirection = "u_light[%1].spotDirection";
    constexpr static const char * const c_uniformLightSpotCutOff = "u_light[%1].spotCutOff";
    constexpr static const char * const c_uniformLightSpotExponent = "u_light[%1].spotExponent";
    constexpr static const char * const c_uniformLightAttenuationEnabled = "u_light[%1].attenuationEnabled";
    constexpr static const char * const c_uniformLightAttenuationFactor = "u_light[%1].attenuationFactor";
    constexpr static const char * const c_uniformMaterialSpecular = "u_material.specular";
    constexpr static const char * const c_uniformMaterialShininess = "u_material.shininess";

    constexpr static const char * const c_attribPosition = "a_position";
    constexpr static const char * const c_attribNormal = "a_normal";
    constexpr static const char * const c_attribColor = "a_color";

    GLShaderProgram();
    ~GLShaderProgram();

    void create();

    void use();
    void unuse();

    void setModelMatrix(const QMatrix4x4 &value);
    void setViewMatrix(const QMatrix4x4 &value);
    void setProjectionMatrix(const QMatrix4x4 &value);

    void setEyePosition(const QVector3D &value);
    void setLightCount(int value);
    void setLight(int lightId, const GlLight &value);
    void setMaterial(const GlMaterial &value);

    void drawPolygon(GLVertexBuffer *vertexBuffer, int first, int count);

private:
    GLuint createShader(GLenum type, const char *name);
    std::string shaderSource(const char *name);
    bool linkProgram();

    void setUniform(const char *name, int value);
    void setUniform(const char *name, bool value);
    void setUniform(const char *name, float value);
    void setUniform(const char *name, const QVector3D &value);
    void setUniform(const char *name, const QVector4D &value);
    void setUniform(const char *name, const QMatrix4x4 &value);

    void setupVertexAttributes(GLVertexBuffer *vertexBuffer);
    void resetVertexAttributes(GLVertexBuffer *vertexBuffer);

    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;
    GLuint m_program = 0;
};

#endif // GLSHADERPROGRAM_H
