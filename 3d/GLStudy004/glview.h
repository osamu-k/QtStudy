#ifndef GLVIEW_H
#define GLVIEW_H

#include "globject.h"

#include <QQuickView>
#include <QVector>
#include <QVector3D>

class GLRenderer;

class GLView : public QQuickView
{
public:
    GLView(QWindow *parent = Q_NULLPTR);
    ~GLView();

private slots:
    void beforeRenderingNotified();

private:
    void createObjects();
    void setupModelMatrix();
    void setupViewMatrix();
    void setupProjectionMatrix();
    void setupLight();

    GLRenderer *m_renderer = nullptr;
    QVector<GLObject *> m_objects;

    QVector3D m_eyePosition;
};

#endif // GLVIEW_H
