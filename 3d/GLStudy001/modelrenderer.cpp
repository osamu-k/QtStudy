#include "modelrenderer.h"

#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>
#include <QThread>

#include <math.h>

#define THREAD_ID QString::number(reinterpret_cast<long>(QThread::currentThread()),16)

#define LOG_ENTER() \
    qDebug() << "ModelRenderer::" << __FUNCTION__ << " enter: line " << __LINE__ << " [" << THREAD_ID << "]";

#define LOG_LEAVE() \
    qDebug() << "ModelRenderer::" << __FUNCTION__ << " leave: line " << __LINE__ << " [" << THREAD_ID << "]";

#define NUM_FACES   6
#define NUM_VERTICE 4

QVector4D ModelRenderer::m_positionArray[] =
{
    // front
    {  0.5,  0.5,  0.5,  1.0 },
    { -0.5,  0.5,  0.5,  1.0 },
    { -0.5, -0.5,  0.5,  1.0 },
    {  0.5, -0.5,  0.5,  1.0 },

    // right
    {  0.5,  0.5, -0.5,  1.0 },
    {  0.5,  0.5,  0.5,  1.0 },
    {  0.5, -0.5,  0.5,  1.0 },
    {  0.5, -0.5, -0.5,  1.0 },

    // back
    { -0.5,  0.5, -0.5,  1.0 },
    {  0.5,  0.5, -0.5,  1.0 },
    {  0.5, -0.5, -0.5,  1.0 },
    { -0.5, -0.5, -0.5,  1.0 },

    // left
    { -0.5,  0.5,  0.5,  1.0 },
    { -0.5,  0.5, -0.5,  1.0 },
    { -0.5, -0.5, -0.5,  1.0 },
    { -0.5, -0.5,  0.5,  1.0 },

    // top
    {  0.5,  0.5,  0.5,  1.0 },
    {  0.5,  0.5, -0.5,  1.0 },
    { -0.5,  0.5, -0.5,  1.0 },
    { -0.5,  0.5,  0.5,  1.0 },

    // bottom
    {  0.5, -0.5,  0.5,  1.0 },
    { -0.5, -0.5,  0.5,  1.0 },
    { -0.5, -0.5, -0.5,  1.0 },
    {  0.5, -0.5, -0.5,  1.0 },
};

QVector4D ModelRenderer::m_colorArray[] =
{
    // front
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },

    // right
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },

    // back
    { 0.0, 0.0, 1.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },

    // left
    { 0.0, 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0, 1.0 },

    // top
    { 1.0, 0.0, 1.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },

    // bottom
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
};

QVector4D ModelRenderer::m_lineColorArray[ NUM_VERTICE * NUM_FACES　];

QVector4D ModelRenderer::m_normalArray[ NUM_VERTICE * NUM_FACES ];

ModelRenderer::ModelRenderer(QQuickItem *parent)
    : QQuickItem(parent)
    , m_window( nullptr )
    , m_useProgram2( false )
    , m_shaderProgram( nullptr )
    , m_shaderProgram2( nullptr )
    , m_rotateX(0.0)
    , m_rotateY(0.0)
    , m_rotateZ(0.0)
    , m_eyeDistance(4.0)
    , m_eyeAngleX(0.0)
    , m_eyeAngleY(0.0)
    , m_lightDistance(8.0)
    , m_lightAngleX(0.0)
    , m_lightAngleY(0.0)
    , m_ambientBrightness(0.5)
    , m_diffuseBrightness(0.75)
    , m_specularBrightness(1.0)
    , m_ambientReflection(0.5)
    , m_diffuseReflection(0.5)
    , m_specularReflection(0.5)
    , m_shininess(100.0)
    , m_spotExponent(1.0)
    , m_cutoffAngle(180.0)
{
    LOG_ENTER();

    QVector4D lineColor( 0.0, 0.0, 0.0, 1.0 );
//    QVector4D lineColor( 1.0, 1.0, 1.0, 1.0 );
    for( int i = 0; i < NUM_VERTICE * NUM_FACES; i++ ){
        m_lineColorArray[i] = lineColor;
    }

    for( int i = 0; i < NUM_FACES; i ++ ){
        QVector3D normal = createPolygonNormal(
                                m_positionArray[NUM_VERTICE * i].toVector3D(),
                                m_positionArray[NUM_VERTICE * i + 1].toVector3D(),
                                m_positionArray[NUM_VERTICE * i + 2].toVector3D() );
        for( int j = 0; j < NUM_VERTICE; j++ ){
            m_normalArray[NUM_VERTICE * i + j] = normal;
        }
    }

    updateEyePosition();
    updateLightPosition();

    connect( this, SIGNAL(windowChanged(QQuickWindow*)),
             this, SLOT(windowChanged(QQuickWindow *)),
             Qt::DirectConnection );

    LOG_LEAVE();
}

ModelRenderer::~ModelRenderer()
{
    LOG_ENTER();
    LOG_LEAVE();
}

QVector3D ModelRenderer::createPolygonNormal( QVector3D a, QVector3D b, QVector3D c ) {

    QVector3D ab( b - a );
    QVector3D bc( c - b );
    QVector3D normal = QVector3D::crossProduct( ab, bc );	//AB BCの外積
    normal.normalize();//単位ベクトルにする
    return normal;
}

void ModelRenderer::windowChanged(QQuickWindow *window)
{
    LOG_ENTER();
    if( window != nullptr && window != m_window ){
        window->setClearBeforeRendering(false);

        connect( window, SIGNAL(afterAnimating()), this, SLOT(afterAnimating()), Qt::DirectConnection );
        connect( window, SIGNAL(afterRendering()), this, SLOT(afterRendering()), Qt::DirectConnection );
        connect( window, SIGNAL(afterSynchronizing()), this, SLOT(afterSynchronizing()), Qt::DirectConnection );
        connect( window, SIGNAL(beforeRendering()), this, SLOT(beforeRendering()), Qt::DirectConnection );
        connect( window, SIGNAL(beforeSynchronizing()), this, SLOT(beforeSynchronizing()), Qt::DirectConnection );
        connect( window, SIGNAL(frameSwapped()), this, SLOT(frameSwapped()), Qt::DirectConnection );
        connect( window, SIGNAL(openglContextCreated(QOpenGLContext*)), this, SLOT(openglContextCreated(QOpenGLContext*)), Qt::DirectConnection );
        connect( window, SIGNAL(sceneGraphError(QQuickWindow::SceneGraphError,QString)), this, SLOT(sceneGraphError(QQuickWindow::SceneGraphError,QString)), Qt::DirectConnection );
        connect( window, SIGNAL(sceneGraphInitialized()), this, SLOT(sceneGraphInitialized()), Qt::DirectConnection );
        connect( window, SIGNAL(sceneGraphInvalidated()), this, SLOT(sceneGraphInvalidated()),Qt::DirectConnection );
    }
    m_window = window;
    LOG_LEAVE();
}

void ModelRenderer::afterAnimating()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::afterRendering()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::afterSynchronizing()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::beforeRendering()
{
    LOG_ENTER();

    //render();
    render2();

    LOG_LEAVE();
}

void ModelRenderer::beforeSynchronizing()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::frameSwapped()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::openglContextCreated(QOpenGLContext *context)
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::sceneGraphAboutToStop()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::sceneGraphError(QQuickWindow::SceneGraphError error, const QString &message)
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::sceneGraphInitialized()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::sceneGraphInvalidated()
{
    LOG_ENTER();
    LOG_LEAVE();
}

void ModelRenderer::updateEyePosition()
{
    float x = 0;
    float y = 0;
    float z = 0;

    y = sin(m_eyeAngleX * 2 * M_PI / 360);
    z = cos(m_eyeAngleX * 2 * M_PI / 360);

    x = z * sin(m_eyeAngleY * 2 * M_PI / 360);
    z = z * cos(m_eyeAngleY * 2 * M_PI / 360);

    m_eyePosition = QVector3D(m_eyeDistance * x,
                              m_eyeDistance * y,
                              m_eyeDistance * z);
}

void ModelRenderer::updateLightPosition()
{
    float x = 0;
    float y = 0;
    float z = 0;

    y = sin(m_lightAngleX * 2 * M_PI / 360);
    z = cos(m_lightAngleX * 2 * M_PI / 360);

    x = z * sin(m_lightAngleY * 2 * M_PI / 360);
    z = z * cos(m_lightAngleY * 2 * M_PI / 360);

    m_lightPosition = QVector4D(m_lightDistance * x,
                                m_lightDistance * y,
                                m_lightDistance * z,
                                1.0);
}

void ModelRenderer::render()
{
    LOG_ENTER();

    initializeOpenGLFunctions();

    //setupShaderProgram();
    setupShaderProgram2();

    setupModelMatrix();
    setupViewMatrix();
    setupProjectionMatrix();

    QSize viewportSize = window()->size() * window()->devicePixelRatio();
    glViewport(0, 0, viewportSize.width(), viewportSize.height());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glClearColor(0, 0, 0, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_shaderProgram->bind();

    m_shaderProgram->setUniformValue("modelMatrix", m_modelMatrix);
    m_shaderProgram->setUniformValue("viewMatrix", m_viewMatrix);
    m_shaderProgram->setUniformValue("projectionMatrix", m_projectionMatrix);

    QMatrix4x4 mvMatrix = m_viewMatrix * m_modelMatrix;
    QMatrix3x3 normalMatrix = mvMatrix.normalMatrix();
    m_shaderProgram->setUniformValue("normalMatrix", normalMatrix );

    m_shaderProgram->setUniformValue("lightPosition", m_lightPosition);
    qDebug() << "lightPosition: " << m_lightPosition;
    m_shaderProgram->setUniformValue("eyePosition", m_eyePosition);

    QVector4D ambientColor( m_ambientBrightness, m_ambientBrightness, m_ambientBrightness, 1.0);
    QVector4D diffuseColor( m_diffuseBrightness, m_diffuseBrightness, m_diffuseBrightness, 1.0);
    QVector4D specularColor( m_specularBrightness, m_specularBrightness, m_specularBrightness, 1.0);
    m_shaderProgram->setUniformValue("ambientColor", ambientColor);
    m_shaderProgram->setUniformValue("diffuseColor", diffuseColor);
    m_shaderProgram->setUniformValue("specularColor", specularColor);

    m_shaderProgram->setUniformValue("ambientReflection", m_ambientReflection);
    m_shaderProgram->setUniformValue("diffuseReflection", m_diffuseReflection);
    m_shaderProgram->setUniformValue("specularReflection", m_specularReflection);
    m_shaderProgram->setUniformValue("shininess", m_shininess);

    m_shaderProgram->enableAttributeArray( "position" );
    m_shaderProgram->enableAttributeArray( "color" );
    m_shaderProgram->enableAttributeArray( "normal" );

    m_shaderProgram->setAttributeArray( "position", m_positionArray );
    m_shaderProgram->setAttributeArray( "normal", m_normalArray );

    m_shaderProgram->setAttributeArray( "color", m_colorArray );
    for( int i = 0; i < NUM_FACES; i++ ){
        glDrawArrays(GL_TRIANGLE_FAN, NUM_VERTICE * i, NUM_VERTICE);
    }

//    glEnable(GL_POLYGON_OFFSET_FILL);
//    glPolygonOffset(0.1, 0.2);
    glLineWidth(2.0);
//    glEnable(GL_LINE_SMOOTH);     // GL_LINE_SMOOTH is not supported in OpenGL ES

    m_shaderProgram->setAttributeArray("color", m_lineColorArray);
    for( int i = 0; i < NUM_FACES; i++ ){
        glDrawArrays(GL_LINE_LOOP, NUM_VERTICE * i, NUM_VERTICE);
    }

    m_shaderProgram->disableAttributeArray( "position" );
    m_shaderProgram->disableAttributeArray( "color" );

    m_shaderProgram->release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    window()->resetOpenGLState();

    LOG_LEAVE();
}

void ModelRenderer::render2()
{
    LOG_ENTER();
    initializeOpenGLFunctions();

    setupShaderProgram2();

    setupModelMatrix();
    setupViewMatrix();
    setupProjectionMatrix();

    QSize viewportSize = window()->size() * window()->devicePixelRatio();
    glViewport(0, 0, viewportSize.width(), viewportSize.height());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_shaderProgram2->bind();

    m_shaderProgram2->setUniformValue("u_modelMatrix", m_modelMatrix);
    m_shaderProgram2->setUniformValue("u_viewMatrix", m_viewMatrix);
    m_shaderProgram2->setUniformValue("u_projectionMatrix", m_projectionMatrix);

    QMatrix4x4 mvMatrix = m_viewMatrix * m_modelMatrix;
    QMatrix3x3 normalMatrix = mvMatrix.normalMatrix();
    m_shaderProgram2->setUniformValue("u_normalMatrix", normalMatrix );

    m_shaderProgram2->setUniformValue("u_lightPosition", m_lightPosition);
    m_shaderProgram2->setUniformValue("u_eyePosition", m_eyePosition);

    QVector4D ambientColor( m_ambientBrightness, m_ambientBrightness, m_ambientBrightness, 1.0);
    QVector4D diffuseColor( m_diffuseBrightness, m_diffuseBrightness, m_diffuseBrightness, 1.0);
    QVector4D specularColor( m_specularBrightness, m_specularBrightness, m_specularBrightness, 1.0);

    /*
    struct light {
        vec4    position;
        vec4    ambient_color;
        vec4    diffuse_color;
        vec4    specular_color;
        vec3    spot_direction;
        vec3    attenuation_factors;
        bool    compute_distance_attenuation;
        float   spot_exponent;
        float   spot_cutoff_angle;
    };
    uniform light u_light;
    */
    QVector4D lightInView = m_viewMatrix * m_lightPosition;
    QVector4D spotDirection = (- (m_viewMatrix * m_lightPosition)).normalized();
    m_shaderProgram2->setUniformValue("u_light.position"                    , lightInView );
    m_shaderProgram2->setUniformValue("u_light.ambient_color"               , ambientColor );
    m_shaderProgram2->setUniformValue("u_light.diffuse_color"               , diffuseColor );
    m_shaderProgram2->setUniformValue("u_light.specular_color"              , specularColor );
    m_shaderProgram2->setUniformValue("u_light.spot_direction"              , spotDirection.toVector3D() );
    m_shaderProgram2->setUniformValue("u_light.attenuation_factors"         , QVector3D(1.0, 1.0, 1.0) );
    m_shaderProgram2->setUniformValue("u_light.compute_distance_attenuation", true );
    m_shaderProgram2->setUniformValue("u_light.spot_exponent"               , (float)100 );
    m_shaderProgram2->setUniformValue("u_light.spot_cutoff_angle"           , m_cutoffAngle );

    /*
    struct material {
        vec4    ambient_color;
        vec4    diffuse_color;
        vec4    specular_color;
        float   specular_exponent;
    };
    uniform material u_material;
    */
    QVector4D materialAmbient( m_ambientReflection, m_ambientReflection, m_ambientReflection, 1.0);
    QVector4D materialDiffuse( m_diffuseReflection, m_diffuseReflection, m_diffuseReflection, 1.0);
    QVector4D materialSpecular( m_specularReflection, m_specularReflection, m_specularReflection, 1.0);

    m_shaderProgram2->setUniformValue("u_material.ambient_color"    , materialAmbient );
    m_shaderProgram2->setUniformValue("u_material.diffuse_color"    , materialDiffuse );
    m_shaderProgram2->setUniformValue("u_material.specular_color"   , materialSpecular );
    m_shaderProgram2->setUniformValue("u_material.specular_exponent", m_shininess );

    m_shaderProgram2->enableAttributeArray( "a_position" );
    m_shaderProgram2->enableAttributeArray( "a_color" );
    m_shaderProgram2->enableAttributeArray( "a_normal" );

    m_shaderProgram2->setAttributeArray( "a_position", m_positionArray );
    m_shaderProgram2->setAttributeArray( "a_normal", m_normalArray );

    m_shaderProgram2->setAttributeArray( "a_color", m_colorArray );
    for( int i = 0; i < NUM_FACES; i++ ){
        glDrawArrays(GL_TRIANGLE_FAN, NUM_VERTICE * i, NUM_VERTICE);
    }

//    glEnable(GL_POLYGON_OFFSET_FILL);
//    glPolygonOffset(0.1, 0.2);
    glLineWidth(2.0);
//    glEnable(GL_LINE_SMOOTH);     // GL_LINE_SMOOTH is not supported in OpenGL ES

    m_shaderProgram2->setAttributeArray("a_color", m_lineColorArray);
    for( int i = 0; i < NUM_FACES; i++ ){
        glDrawArrays(GL_LINE_LOOP, NUM_VERTICE * i, NUM_VERTICE);
    }

    m_shaderProgram2->disableAttributeArray( "a_position" );
    m_shaderProgram2->disableAttributeArray( "a_color" );

    m_shaderProgram2->release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    window()->resetOpenGLState();

    LOG_LEAVE();
}

void ModelRenderer::setupShaderProgram()
{
    LOG_ENTER();

    if( m_shaderProgram == nullptr ){
        m_shaderProgram = new QOpenGLShaderProgram;
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertexshader.vsh");
        m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentshader.fsh");
        m_shaderProgram->link();
    }

    LOG_LEAVE();
}

void ModelRenderer::setupShaderProgram2()
{
    LOG_ENTER();

    if( m_shaderProgram2 == nullptr ){
        m_shaderProgram2 = new QOpenGLShaderProgram;
        m_shaderProgram2->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertexshader2.vsh");
        m_shaderProgram2->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentshader2.fsh");
        m_shaderProgram2->link();
    }

    LOG_LEAVE();
}

void ModelRenderer::setupModelMatrix()
{
    LOG_ENTER();

    m_modelMatrix.setToIdentity();
    m_modelMatrix.rotate(m_rotateX, 1.0, 0.0, 0.0);
    m_modelMatrix.rotate(m_rotateY, 0.0, 1.0, 0.0);
    m_modelMatrix.rotate(m_rotateZ, 0.0, 0.0, 1.0);

    LOG_LEAVE();
}

void ModelRenderer::setupViewMatrix()
{
    LOG_ENTER();

//    float x = 0;
//    float y = 0;
//    float z = 0;

//    y = sin(m_eyeAngleX * 2 * M_PI / 360);
//    z = cos(m_eyeAngleX * 2 * M_PI / 360);

//    x = z * sin(m_eyeAngleY * 2 * M_PI / 360);
//    z = z * cos(m_eyeAngleY * 2 * M_PI / 360);

//    QVector3D eyePosition = QVector3D(m_eyeDistance * x,
//                                      m_eyeDistance * y,
//                                      m_eyeDistance * z);

    float upX = 0;
    float upY = 0;
    float upZ = 0;

    upY = cos(m_eyeAngleX * 2 * M_PI / 360);
    upZ = - sin(m_eyeAngleX * 2 * M_PI / 360);

    upX = upZ * sin(m_eyeAngleY * 2 * M_PI / 360);
    upZ =upZ * cos(m_eyeAngleY * 2 * M_PI / 360);

    QVector3D eyeUpDirection = QVector3D(upX,upY,upZ);
    eyeUpDirection.normalize();

    qDebug() << "eyeAngleX: " << m_eyeAngleX;
    qDebug() << "eyeAngleY: " << m_eyeAngleY;
    qDebug() << "eyePosition: " << m_eyePosition;

    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt( m_eyePosition.toVector3D(), QVector3D(0.0, 0.0, 0.0), eyeUpDirection );

    qDebug() << "m_viewMatrix: " << m_viewMatrix;

    LOG_LEAVE();
}

void ModelRenderer::setupProjectionMatrix()
{
    LOG_ENTER();

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(60.0, (float)window()->width() / (float)window()->height(), 0.001, 1000);

    LOG_LEAVE();
}

void ModelRenderer::setRotateX(float value)
{
    if( m_rotateX != value ){
        m_rotateX = value;
        emit rotateXChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setRotateY(float value)
{
    if( m_rotateY != value ){
        m_rotateY = value;
        emit rotateYChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setRotateZ(float value)
{
    if( m_rotateZ != value ){
        m_rotateZ = value;
        emit rotateZChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setEyeDistance(float value)
{
    if( m_eyeDistance != value ){
        m_eyeDistance = value;
        updateEyePosition();
        emit eyeDistanceChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setEyeAngleX(float value)
{
    if( m_eyeAngleX != value ){
        m_eyeAngleX = value;
        updateEyePosition();
        emit eyeAngleXChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setEyeAngleY(float value)
{
    if( m_eyeAngleY != value ){
        m_eyeAngleY = value;
        updateEyePosition();
        emit eyeAngleYChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setLightDistance(float value)
{
    if( m_lightDistance != value ){
        m_lightDistance = value;
        updateLightPosition();
        emit lightDistanceChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setLightAngleX(float value)
{
    if( m_lightAngleX != value ){
        m_lightAngleX = value;
        updateLightPosition();
        emit lightAngleXChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setLightAngleY(float value)
{
    if( m_lightAngleY != value ){
        m_lightAngleY = value;
        updateLightPosition();
        emit lightAngleYChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setAmbientBrightness(float value)
{
    if( m_ambientBrightness != value ){
        m_ambientBrightness = value;
        emit ambientBrightnessChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setDiffuseBrightness(float value)
{
    if( m_diffuseBrightness != value ){
        m_diffuseBrightness = value;
        emit diffuseBrightnessChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setSpecularBrightness(float value)
{
    if( m_specularBrightness != value ){
        m_specularBrightness = value;
        emit specularBrightnessChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setAmbientReflection(float value)
{
    if( m_ambientReflection != value ){
        m_ambientReflection = value;
        emit ambientReflectionChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setDiffuseReflection(float value)
{
    if( m_diffuseReflection != value ){
        m_diffuseReflection = value;
        emit diffuseReflectionChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setSpecularReflection(float value)
{
    if( m_specularReflection != value ){
        m_specularReflection = value;
        emit specularReflectionChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setShininess(float value)
{
    if( m_shininess != value ){
        m_shininess = value;
        emit shininessChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setSpotExponent(float value)
{
    if( m_spotExponent != value ){
        m_spotExponent = value;
        emit spotExponentChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}

void ModelRenderer::setCutoffAngle(float value)
{
    if( m_cutoffAngle != value ){
        m_cutoffAngle = value;
        emit cutoffAngleChanged(value);
        if( m_window != nullptr ){
            m_window->update();
        }
    }
}
