#ifndef GLVIEW_H
#define GLVIEW_H

#include "globject.h"
#include "cvopenglrenderer.h"

#include <QQuickView>

#include <vector>

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

    void draw();

    std::vector<GLObject *> m_objects;

    CVOpenGLRenderer *m_renderer = nullptr;
};

#endif // GLVIEW_H
