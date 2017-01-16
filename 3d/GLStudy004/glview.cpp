#include "glview.h"

#include "common.h"
#include "glrenderer.h"
#include "globjectcube.h"

#include <math.h>

GLView::GLView(QWindow *parent)
    : QQuickView(parent)
{
    LOG_METHOD_CALLED;

    setClearBeforeRendering(false);

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

    resetOpenGLState();

    static bool initialized = false;
    if( ! initialized ){
        initialized = true;
        m_renderer = GLRenderer::instance();

        createObjects();
    }

    setupModelMatrix();
    setupViewMatrix();
    setupProjectionMatrix();
    setupLight();

    m_renderer->startRendering();

    for( auto object : m_objects ){
        object->draw();
    }

    resetOpenGLState();
}

void GLView::createObjects()
{
    GLObject *cube = new GLObjectCube;
    cube->create();
    m_objects.push_back(cube);
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

    QVector3D eyePosition(3,4,7);
    QMatrix4x4 matrix;
    matrix.lookAt(eyePosition,QVector3D(0,0,0),QVector3D(0,1,0));

    m_renderer->setViewMatrix(matrix);
    m_renderer->setEyePosition(eyePosition);
}

void GLView::setupProjectionMatrix()
{
    LOG_METHOD_CALLED;

    QSizeF surfaceSize = m_renderer->surfaceSize();

    QMatrix4x4 matrix;
    if( surfaceSize.width() > surfaceSize.height() ){
        float ratio = surfaceSize.width() / surfaceSize.height();
        matrix.frustum(-ratio, ratio, -1.0f, 1.0f, 5.0f, 10.0f);
    }
    else{
        float ratio = surfaceSize.height() / surfaceSize.width();
        matrix.frustum(-1.0f, 1.0f, -ratio, ratio, 5.0f, 10.0f);
    }
    m_renderer->setProjectionMatrix(matrix);
}

void GLView::setupLight()
{
    LOG_METHOD_CALLED;

    int lightCount = 1;
//    GlLight light = {
//        {0.0, 0.0, 2.0},        //    QVector3D position;  // in world space.
//        {0.2, 0.2, 0.2, 1.0},   //    QVector4D ambient;
//        {0.5, 0.5, 0.5, 1.0},   //    QVector4D diffuse;
//        {0.5, 0.5, 0.5, 1.0},   //    QVector4D specular;
//        false,                   //     bool spotEnabled;
//        {0.0, 0.0, -2.0},       //    QVector3D spotDirection;
//        30.0,                   //    float spotCutOff;
//        10.0,                    //    float spotExponent;
//        true,                   //    bool attenuationEnabled;
//        {1.0, 0.1, 0.03},       //    QVector3D attenuationFactor;
//    };
//    GlMaterial material = {
//        ////    QVector4D ambient;
//        ////    QVector4D diffuse;
//        {0.5, 0.5, 0.5, 1.0},   //    QVector4D specular;
//        10.0                    //    float shininess;
//    };
    GlLight light = {
        {0.0, 0.0, 2.0},        //    QVector3D position;  // in world space.
        {0.2, 0.2, 0.2},   //    QVector4D ambient;
        {0.5, 0.5, 0.5},   //    QVector4D diffuse;
        {0.5, 0.5, 0.5},   //    QVector4D specular;
        false,                   //     bool spotEnabled;
        {0.0, 0.0, -2.0},       //    QVector3D spotDirection;
        30.0,                   //    float spotCutOff;
        10.0,                    //    float spotExponent;
        true,                   //    bool attenuationEnabled;
        {1.0, 0.1, 0.03},       //    QVector3D attenuationFactor;
    };
    GlMaterial material = {
        ////    QVector4D ambient;
        ////    QVector4D diffuse;
        {0.5, 0.5, 0.5},   //    QVector4D specular;
        10.0                    //    float shininess;
    };

    light.position = lightPosition();
    qDebug() << "light.position = " << light.position;
    m_renderer->setLightCount(lightCount);
    m_renderer->setLight(0, light);
    m_renderer->setMaterial(material);
}

void GLView::setLightDistance( float value ){
    LOG_METHOD_CALLED;
    qDebug() << "value = " << value;

    if( m_lightDistance != value ){
        m_lightDistance = value;
        emit lightDistanceChanged();
        update();
    }
}

float GLView::lightDistance() const
{
    LOG_METHOD_CALLED;

    return m_lightDistance;
}


void GLView::setLightAngleX( float value )
{
    LOG_METHOD_CALLED;
    qDebug() << "value = " << value;

    if( m_lightAngleX != value ){
        m_lightAngleX = value;
        emit lightAngleXChanged();
        update();
    }
}

float GLView::lightAngleX() const
{
    LOG_METHOD_CALLED;

    return m_lightAngleX;
}

void GLView::setLightAngleY( float value )
{
    LOG_METHOD_CALLED;
    qDebug() << "value = " << value;

    if( m_lightAngleY != value ){
        m_lightAngleY = value;
        emit lightAngleYChanged();
        update();
    }
}

float GLView::lightAngleY() const
{
    LOG_METHOD_CALLED;

    return m_lightAngleY;
}

QVector3D GLView::lightPosition()
{
    float x = 0;
    float y = 0;
    float z = 0;

    y = sin(m_lightAngleX * 2 * M_PI / 360);
    z = cos(m_lightAngleX * 2 * M_PI / 360);

    x = z * sin(m_lightAngleY * 2 * M_PI / 360);
    z = z * cos(m_lightAngleY * 2 * M_PI / 360);

    return QVector3D( m_lightDistance * x,
                      m_lightDistance * y,
                      m_lightDistance * z );
}
