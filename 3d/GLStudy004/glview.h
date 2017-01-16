#ifndef GLVIEW_H
#define GLVIEW_H

#include "globject.h"

#include <QQuickView>
#include <QVector>
#include <QVector3D>

class GLRenderer;

class GLView : public QQuickView
{
    Q_OBJECT

    Q_PROPERTY(float lightDistance READ lightDistance WRITE setLightDistance NOTIFY lightDistanceChanged)
    Q_PROPERTY(float lightAngleX READ lightAngleX WRITE setLightAngleX NOTIFY lightAngleXChanged)
    Q_PROPERTY(float lightAngleY READ lightAngleY WRITE setLightAngleY NOTIFY lightAngleYChanged)

public:
    GLView(QWindow *parent = Q_NULLPTR);
    ~GLView();

    void setLightDistance( float value );
    float lightDistance() const;

    void setLightAngleX( float value );
    float lightAngleX() const;

    void setLightAngleY( float value );
    float lightAngleY() const;

signals:
    void lightDistanceChanged();
    void lightAngleXChanged();
    void lightAngleYChanged();

private slots:
    void beforeRenderingNotified();

private:
    void createObjects();
    void setupModelMatrix();
    void setupViewMatrix();
    void setupProjectionMatrix();
    void setupLight();
    QVector3D lightPosition();

    GLRenderer *m_renderer = nullptr;
    QVector<GLObject *> m_objects;

    QVector3D m_eyePosition;

    float m_lightDistance = 3.0;
    float m_lightAngleX = 0.0;
    float m_lightAngleY = 0.0;
};

#endif // GLVIEW_H
