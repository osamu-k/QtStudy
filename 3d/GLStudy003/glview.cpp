#include "common.h"
#include "glview.h"
#include "globjecttriangle.h"

#include <QMatrix4x4>
#include <QVector3D>

GLView::GLView(QWindow *parent)
    : QQuickView(parent)
{
    LOG_METHOD_CALLED;

    setClearBeforeRendering(false);

    // ! Qt::DirectConnection is very important !
    connect(this, &QQuickWindow::beforeRendering,
            this, &GLView::beforeRenderingNotified,
            Qt::DirectConnection);
}

GLView::~GLView()
{
    LOG_METHOD_CALLED;
}

void GLView::beforeRenderingNotified()
{
    LOG_METHOD_CALLED;

    static bool initialized = false;
    if( ! initialized ){
        initialized = true;

        m_renderer = CVOpenGLRenderer::instance();
        createObjects();
    }

    m_renderer->startRendering();

    setupModelMatrix();
    setupViewMatrix();
    setupProjectionMatrix();

    draw();

    resetOpenGLState();
}

void GLView::createObjects()
{
    GLObject *object = new GLObjectTriangle;
    object->create();
    m_objects.push_back(object);
}

void GLView::setupModelMatrix()
{
    LOG_METHOD_CALLED;

    QMatrix4x4 matrix;
    matrix.scale(1.5);
    m_renderer->setModelMatrix(matrix);
}

void GLView::setupViewMatrix()
{
    LOG_METHOD_CALLED;

    QMatrix4x4 matrix;
    matrix.lookAt(QVector3D(3,4,5),QVector3D(0,0,0),QVector3D(0,1,0));
    m_renderer->setViewMatrix(matrix);
}

void GLView::setupProjectionMatrix()
{
    LOG_METHOD_CALLED;

    QMatrix4x4 matrix;
    matrix.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 9.0f);
    m_renderer->setProjectionMatrix(matrix);
}

void GLView::draw()
{
    LOG_METHOD_CALLED;

    for( auto object : m_objects ){
        object->draw();
    }
}
