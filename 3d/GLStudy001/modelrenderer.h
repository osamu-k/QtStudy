#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLFunctions>
#include <QQuickItem>
#include <QQuickWindow>
#include <QVector4D>

class QOpenGLContext;
class QOpenGLShaderProgram;

class ModelRenderer : public QQuickItem, private QOpenGLFunctions
{
    Q_OBJECT

    Q_PROPERTY(float rotateX READ rotateX WRITE setRotateX NOTIFY rotateXChanged)
    Q_PROPERTY(float rotateY READ rotateY WRITE setRotateY NOTIFY rotateYChanged)
    Q_PROPERTY(float rotateZ READ rotateZ WRITE setRotateZ NOTIFY rotateZChanged)

    Q_PROPERTY(float eyeDistance READ eyeDistance WRITE setEyeDistance NOTIFY eyeDistanceChanged)
    Q_PROPERTY(float eyeAngleX READ eyeAngleX WRITE setEyeAngleX NOTIFY eyeAngleXChanged)
    Q_PROPERTY(float eyeAngleY READ eyeAngleY WRITE setEyeAngleY NOTIFY eyeAngleYChanged)

    Q_PROPERTY(float lightDistance READ lightDistance WRITE setLightDistance NOTIFY lightDistanceChanged)
    Q_PROPERTY(float lightAngleX READ lightAngleX WRITE setLightAngleX NOTIFY lightAngleXChanged)
    Q_PROPERTY(float lightAngleY READ lightAngleY WRITE setLightAngleY NOTIFY lightAngleYChanged)

    Q_PROPERTY(float ambientBrightness READ ambientBrightness WRITE setAmbientBrightness NOTIFY ambientBrightnessChanged)
    Q_PROPERTY(float diffuseBrightness READ diffuseBrightness WRITE setDiffuseBrightness NOTIFY diffuseBrightnessChanged)
    Q_PROPERTY(float specularBrightness READ specularBrightness WRITE setSpecularBrightness NOTIFY specularBrightnessChanged)

    Q_PROPERTY(float ambientReflection READ ambientReflection WRITE setAmbientReflection NOTIFY ambientReflectionChanged)
    Q_PROPERTY(float diffuseReflection READ diffuseReflection WRITE setDiffuseReflection NOTIFY diffuseReflectionChanged)
    Q_PROPERTY(float specularReflection READ specularReflection WRITE setSpecularReflection NOTIFY specularReflectionChanged)

    Q_PROPERTY(float shininess READ shininess WRITE setShininess NOTIFY shininessChanged)

    Q_PROPERTY(float spotExponent READ spotExponent WRITE setSpotExponent NOTIFY spotExponentChanged)
    Q_PROPERTY(float cutoffAngle READ cutoffAngle WRITE setCutoffAngle NOTIFY cutoffAngleChanged)

public:
    explicit ModelRenderer(QQuickItem *parent = Q_NULLPTR);
    virtual ~ModelRenderer();

    void setRotateX(float value);
    float rotateX() const { return m_rotateX; }

    void setRotateY(float value);
    float rotateY() const { return m_rotateY; }

    void setRotateZ(float value);
    float rotateZ() const { return m_rotateZ; }

    void setEyeDistance(float value);
    float eyeDistance() const { return m_eyeDistance; }

    void setEyeAngleX(float value);
    float eyeAngleX() const { return m_eyeAngleX; }

    void setEyeAngleY(float value);
    float eyeAngleY() const { return m_eyeAngleY; }

    void setLightDistance(float value);
    float lightDistance() const { return m_lightDistance; }

    void setLightAngleX(float value);
    float lightAngleX() const { return m_lightAngleX; }

    void setLightAngleY(float value);
    float lightAngleY() const { return m_lightAngleY; }

    void setAmbientBrightness(float value);
    float ambientBrightness() const { return m_ambientBrightness; }

    void setDiffuseBrightness(float value);
    float diffuseBrightness() const { return m_diffuseBrightness; }

    void setSpecularBrightness(float value);
    float specularBrightness() const { return m_specularBrightness; }

    void setAmbientReflection(float value);
    float ambientReflection() const { return m_ambientReflection; }

    void setDiffuseReflection(float value);
    float diffuseReflection() const { return m_diffuseReflection; }

    void setSpecularReflection(float value);
    float specularReflection() const { return m_specularReflection; }

    void setShininess(float value);
    float shininess() const { return m_shininess; }

    void setSpotExponent(float value);
    float spotExponent() const { return m_spotExponent; }

    void setCutoffAngle(float value);
    float cutoffAngle() const { return m_cutoffAngle; }

signals:
    void rotateXChanged(float);
    void rotateYChanged(float);
    void rotateZChanged(float);
    void eyeDistanceChanged(float);
    void eyeAngleXChanged(float);
    void eyeAngleYChanged(float);
    void lightDistanceChanged(float);
    void lightAngleXChanged(float);
    void lightAngleYChanged(float);
    void ambientBrightnessChanged(float);
    void diffuseBrightnessChanged(float);
    void specularBrightnessChanged(float);
    void ambientReflectionChanged(float);
    void diffuseReflectionChanged(float);
    void specularReflectionChanged(float);
    void shininessChanged(float);
    void spotExponentChanged(float);
    void cutoffAngleChanged(float);

public slots:

private slots:
    void windowChanged(QQuickWindow *window);

    void afterAnimating();
    void afterRendering();
    void afterSynchronizing();
    void beforeRendering();
    void beforeSynchronizing();
    void frameSwapped();
    void openglContextCreated(QOpenGLContext *context);
    void sceneGraphAboutToStop();
    void sceneGraphError(QQuickWindow::SceneGraphError error, const QString &message);
    void sceneGraphInitialized();
    void sceneGraphInvalidated();

private:
    QVector3D createPolygonNormal( QVector3D a, QVector3D b, QVector3D c );
    void updateEyePosition();
    void updateLightPosition();
    void render();
    void render2();
    void setupShaderProgram();
    void setupShaderProgram2();
    void setupModelMatrix();
    void setupViewMatrix();
    void setupProjectionMatrix();

    QQuickWindow *m_window;
    bool m_useProgram2;
    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLShaderProgram *m_shaderProgram2;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;

    float m_rotateX;
    float m_rotateY;
    float m_rotateZ;

    float m_eyeDistance;
    float m_eyeAngleX;
    float m_eyeAngleY;
    QVector4D m_eyePosition;

    float m_lightDistance;
    float m_lightAngleX;
    float m_lightAngleY;
    QVector4D m_lightPosition;

    float m_ambientBrightness;
    float m_diffuseBrightness;
    float m_specularBrightness;

    float m_ambientReflection;
    float m_diffuseReflection;
    float m_specularReflection;
    float m_shininess;
    float m_spotExponent;
    float m_cutoffAngle;

//    QVector3D m_spotDirection;
//    QVector3D m_attenuationFactors;
//    float m_spotExponent;
//    float m_spotCutoffAngle;
//    bool m_computeDistanceAttenuation;

    static QVector4D m_positionArray[];
    static QVector4D m_colorArray[];
    static QVector4D m_lineColorArray[];
    static QVector4D m_normalArray[];
};

#endif // MODELRENDERER_H
