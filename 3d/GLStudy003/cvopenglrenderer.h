#ifndef CVOPENGLRENDERER_H
#define CVOPENGLRENDERER_H

#include "cvopenglfunctions.h"
#include "cvopenglshaderprogram.h"

#include <QMatrix4x4>

#include <map>

class CVOpenGLRenderer
{
public:
    static CVOpenGLRenderer *instance();

    void startRendering();
    void finishRendering();

    enum ShaderProgramId{
        CommonShader,
    };

    CVOpenGLShaderProgram *getShaderProgram(ShaderProgramId id);

    void setModelMatrix(const QMatrix4x4 &value);
    void setViewMatrix(const QMatrix4x4 &value);
    void setProjectionMatrix(const QMatrix4x4 &value);

    void useProgram(CVOpenGLShaderProgram *program);

private:
    CVOpenGLRenderer();
    ~CVOpenGLRenderer();

    CVOpenGLFunctions *m_gl = nullptr;
    std::map<ShaderProgramId, CVOpenGLShaderProgram *> m_shaderMap;

    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;

    static CVOpenGLRenderer *m_instance;
};

#endif // CVOPENGLRENDERER_H
