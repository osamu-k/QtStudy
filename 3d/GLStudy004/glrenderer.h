#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "glcommon.h"
#include "glshaderprogram.h"

#include <QMatrix4x4>
#include <QOpenGLFunctions>

class GLShaderProgram;
class GLVertexBuffer;

class GLRenderer : public QOpenGLFunctions
{
public:
    static GLRenderer *instance();

    void create();

    GLShaderProgram *getShaderProgram();

    void setModelMatrix(const QMatrix4x4 value);
    void setViewMatrix(const QMatrix4x4 value);
    void setProjectionMatrix(const QMatrix4x4 value);

    void setEyePosition(const QVector3D &value);
    void setLightCount(int value);
    void setLight(int lightId, const GlLight &value);
    void setMaterial(const GlMaterial &value);

    void startRendering();

    void drawPolygon(
            GLShaderProgram *program,
            GLVertexBuffer *vertexBuffer,
            int first,
            int count );

private:
    GLRenderer();
    ~GLRenderer();

    static GLRenderer *m_instance;

    GLShaderProgram *m_program = nullptr;

    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;

    QVector3D m_eyePosition;
    int m_lightCount = 0;
    GlLight m_light[8];
    GlMaterial m_material;
};

#endif // GLRENDERER_H
