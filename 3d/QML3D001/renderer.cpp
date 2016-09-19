#include "renderer.h"
#include <QDebug>
#include <QOpenGLPixelTransferOptions>
#include <QPainter>
#include <QThread>

QVector3D Renderer::m_cubeVertices[NUM_VERTICES] = {
    { -0.5, -0.5, +0.5 },   // bottom-left-front
    { +0.5, -0.5, +0.5 },   // bottom-right-front
    { +0.5, +0.5, +0.5 },   // top-right-front
    { -0.5, +0.5, +0.5 },   // top-left-front
    { -0.5, -0.5, -0.5 },   // bottom-left-back
    { +0.5, -0.5, -0.5 },   // bottom-right-back
    { +0.5, +0.5, -0.5 },   // top-right-back
    { -0.5, +0.5, -0.5 },   // top-left-back
};

GLubyte Renderer::m_cubeVertexIndices[NUM_FACES * 6] = {
    0, 1, 2, 0, 2, 3,   // front face
    3, 2, 6, 3, 6, 7,   // upper face
    1, 5, 6, 1, 6, 2,   // right face
    4, 5, 1, 4, 1, 0,   // lower face
    4, 0, 3, 4, 3, 7,   // left face
    5, 4, 7, 5, 7, 6    // back face
};

QVector3D Renderer::m_cubeColors[NUM_FACES] = {
    { 1.0, 0.0, 0.0}, // front face - RED
    { 1.0, 1.0, 0.0}, // upper face - yellow
    { 0.0, 1.0, 0.0}, // right face - green
    { 0.0, 0.0, 1.0}, // lower face - blue
    { 1.0, 0.0, 1.0}, // left face - mazenta
    { 0.0, 1.0, 1.0}  // back face - cyan
};

QVector2D Renderer::m_textureCoordinates[6] ={
    { 0, 0 }, { 1, 0 }, { 1, 1 },
    { 0, 0 }, { 1, 1 }, { 0, 1 }
};

Renderer::Renderer(QQuickItem *parent)
    : QQuickItem(parent)
    , m_distance( 2.0 )
    , m_lightAngle( 0 )
    , m_useTexture( false )
    , m_useLight( false )
    , m_useBuffer( false )
    , m_initialized( false )
    , m_program( nullptr )
    , m_texture( nullptr )
    , m_buffer( nullptr )
    , m_bufferOffsetVertex( 0 )
    , m_bufferOffsetColor( 0 )
    , m_bufferOffsetTexCoord( 0 )
    , m_bufferOffsetNormal( 0 )
    , m_bufferTupleSize( 0 )
    , m_updateTexture( false )
    , m_image( 10*31*NUM_FACES, 10*31, QImage::Format_RGBA8888 )
    , m_cellSize( 10 )
    , m_cellCount( 31 )
{
    createArrays();

    m_rotationMatrix.rotate(-25,0,1,0);
    m_rotationMatrix.rotate(25,1,0,0);

    connect( this, SIGNAL(windowChanged(QQuickWindow*)),
             this, SLOT(handleWindowChange(QQuickWindow*)),
             Qt::DirectConnection );
    connect( &m_lifeGame, SIGNAL(allChanged()), this, SLOT(lifeGameChanged()) );
}

Renderer::~Renderer()
{
//    if( m_buffer != nullptr ){
//        m_buffer->destroy();
//        delete m_buffer;
//        m_buffer = nullptr;
//    }
//    if( m_texture != nullptr ){
//        m_texture->destroy();
//        delete m_texture;
//        m_texture = nullptr;
//    }
//    if( m_program != nullptr ){
//        delete m_program;
//        m_program = nullptr;
//    }
}

void Renderer::setDistance( double value )
{
    if( m_distance != value ){
        m_distance = value;
        if( window() != nullptr ){
            window()->update();
        }
        emit distanceChanged( m_distance );
    }
}

double Renderer::distance() const
{
    return m_distance;
}

void Renderer::setLightAngle( double value )
{
    if( m_lightAngle != value ){
        m_lightAngle = value;
        if( window() != nullptr ){
            window()->update();
        }
        emit lightAngleChanged( m_lightAngle );
    }
}

double Renderer::lightAngle() const
{
    return m_lightAngle;
}

void Renderer::setUseTexture( bool value )
{
    if( m_useTexture != value ){
        m_useTexture = value;

        if( m_useTexture ){
            m_lifeGame.start();
            lifeGameChanged();
        }
        else{
            m_lifeGame.stop();
        }

        if( window() != nullptr ){
            window()->update();
        }
        emit useTextureChanged( m_useTexture );
    }
}

bool Renderer::useTexture() const
{
    return m_useTexture;
}

void Renderer::setUseLight( bool value )
{
    if( m_useLight != value ){
        m_useLight = value;
        if( window() != nullptr ){
            window()->update();
        }
        emit useLightChanged( m_useLight );
    }
}

bool Renderer::useLight() const
{
    return m_useLight;
}

void Renderer::setUseBuffer( bool value )
{
    if( m_useBuffer != value ){
        m_useBuffer = value;
        if( window() != nullptr ){
            window()->update();
        }
        emit useBufferChanged( m_useBuffer );
    }
}

bool Renderer::useBuffer() const
{
    return m_useBuffer;
}

void Renderer::createArrays()
{
    createArrayVertex();
    createArrayColor();
    createArrayTexCoord();
    createArrayNormal();
}

void Renderer::createArrayVertex()
{
    for( int i = 0; i < NUM_FACES * 6; i++ ){
        int index = m_cubeVertexIndices[i];
        m_arrayVertex << m_cubeVertices[index];
    }
}

void Renderer::createArrayColor()
{
    for( int i = 0; i < NUM_FACES; i++ ){
        for( int j = 0; j < 6; j++ ){
            m_arrayColor << m_cubeColors[i];
        }
    }
}

void Renderer::createArrayTexCoord()
{
    for( int i = 0; i < NUM_FACES; i++ ){
        for( int j = 0; j < 6; j++ ){
            QVector2D vector( (1.0 / NUM_FACES) * i + (m_textureCoordinates[j].x() / NUM_FACES),
                              m_textureCoordinates[j].y() );
            m_arrayTexCoord << vector;
        }
    }
}

void Renderer::createArrayNormal()
{
    for( int i = 0; i < NUM_FACES * 6; i += 3 ){
        QVector3D normal = createPolygonNormal( m_arrayVertex[i],
                                                m_arrayVertex[i+1],
                                                m_arrayVertex[i+2]);
        m_arrayNormal << normal;
        m_arrayNormal << normal;
        m_arrayNormal << normal;
    }
}

QVector3D Renderer::createPolygonNormal( QVector3D a, QVector3D b, QVector3D c ) {

    QVector3D ab( b - a );
    QVector3D bc( c - b );
    QVector3D normal = QVector3D::crossProduct( ab, bc );	//AB BCの外積
    normal.normalize();//単位ベクトルにする
    return normal;
}

void Renderer::calculateMvpMatrix()
{
    m_mMatrix.setToIdentity();
    m_mMatrix = m_rotationMatrix;

    QMatrix4x4 cameraTransformation;

    QVector3D cameraPosition = cameraTransformation * QVector3D(0,0,m_distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0,1,0);

    m_vMatrix.setToIdentity();
    m_vMatrix.lookAt(cameraPosition, QVector3D(0,0,0), cameraUpDirection);

    m_pMatrix.setToIdentity();
    m_pMatrix.perspective(60.0, (float)window()->width() / (float)window()->height(), 0.001, 1000);

    m_mvMatrix = m_vMatrix * m_mMatrix;
    m_mvpMatrix = m_pMatrix * m_vMatrix * m_mMatrix;
}

void Renderer::calculateLightingMatrix()
{
    m_mMatrix.setToIdentity();

    QMatrix4x4 cameraTransformation;

    QVector3D cameraPosition = cameraTransformation * QVector3D(0,0,m_distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0,1,0);

    m_vLightingMatrix.setToIdentity();
    m_vLightingMatrix.lookAt(cameraPosition, QVector3D(0,0,0), cameraUpDirection);

    m_pLightingMatrix.setToIdentity();
    m_pLightingMatrix.perspective(60.0, (float)window()->width() / (float)window()->height(), 0.001, 1000);

    m_mvLightingMatrix = m_vLightingMatrix * m_mLightingMatrix;
    m_mvpLightingMatrix = m_pLightingMatrix * m_vLightingMatrix * m_mLightingMatrix;
}

void Renderer::handleWindowChange(QQuickWindow *window)
{
    if( window != nullptr ){
        connect( window, SIGNAL(beforeRendering()),
                 this, SLOT(render()),
                 Qt::DirectConnection );
        window->setClearBeforeRendering(false);
    }
}

void Renderer::createShaderProgram()
{
    if( m_program == nullptr ){
        m_program = new QOpenGLShaderProgram;
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vertexshader.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentshader.frag");
        m_program->link();
    }
}

QImage Renderer::createTextureImage()
{
    QPainter painter( &m_image );
    for( int i = 0; i < NUM_FACES; i++ ){
        QColor color( int(255 * m_cubeColors[i].x()),
                      int(255 * m_cubeColors[i].y()),
                      int(255 * m_cubeColors[i].z()),
                      255 );

        QColor deadColor = color;
        QColor aliveColor = QColor( 255 - color.red(),
                                    255 - color.green(),
                                    255 - color.blue(),
                                    color.alpha());

        QBrush brushAlive( aliveColor );
        QBrush brushDead( deadColor );

        painter.setPen( Qt::black );

        int offsetX = m_cellCount / 2;
        int offsetY = m_cellCount / 2;
        for( int row = 0; row < m_cellCount; row++ ){
            for( int column = 0; column < m_cellCount; column++ ){
                if( m_lifeGame.isLifeInCell( row - offsetX, column - offsetY ) ){
                    painter.setBrush( brushAlive );
                }
                else{
                    painter.setBrush( brushDead );
                }
                painter.drawRect( column * m_cellSize, row * m_cellSize,
                                  m_cellSize, m_cellSize );
            }
        }

        painter.translate( m_image.width() / NUM_FACES, 0 );
    }

    return m_image;
}

void Renderer::updateTexture()
{
    if( m_updateTexture ){
        m_updateTexture = false;

        if( m_texture == nullptr ){
            m_texture = new QOpenGLTexture( QOpenGLTexture::Target2D );
            m_texture->setFormat( QOpenGLTexture::RGBAFormat );
            m_texture->setSize( m_image.width(), m_image.height() );
            m_texture->setMipLevels( 1 );
            m_texture->setMinificationFilter( QOpenGLTexture::Linear );
            m_texture->setMagnificationFilter( QOpenGLTexture::Linear );
            m_texture->allocateStorage( QOpenGLTexture::RGBA, QOpenGLTexture::UInt8 );
        }

        m_image = createTextureImage().mirrored();
        QOpenGLPixelTransferOptions options;
        options.setAlignment(1);
        m_texture->setData(0, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, m_image.constBits(), &options);
    }
}

void Renderer::createBufferObject()
{
    if( m_buffer == nullptr ){
        QVector<GLfloat> buffer;
        for( int i = 0; i < NUM_FACES * 6; i++ ){
            buffer << m_arrayVertex[i].x();
            buffer << m_arrayVertex[i].y();
            buffer << m_arrayVertex[i].z();
            buffer << m_arrayColor[i].x();
            buffer << m_arrayColor[i].y();
            buffer << m_arrayColor[i].z();
            buffer << m_arrayTexCoord[i].x();
            buffer << m_arrayTexCoord[i].y();
            buffer << m_arrayNormal[i].x();
            buffer << m_arrayNormal[i].y();
            buffer << m_arrayNormal[i].z();
        }

        m_buffer = new QOpenGLBuffer;
        m_buffer->create();
        m_buffer->bind();
        m_buffer->allocate( buffer.constData(),
                            buffer.count() * sizeof(GLfloat) );
        m_buffer->release();

        m_bufferOffsetVertex = 0;
        m_bufferOffsetColor = m_bufferOffsetVertex + 3 * sizeof(GLfloat);
        m_bufferOffsetTexCoord = m_bufferOffsetColor + 3 * sizeof(GLfloat);
        m_bufferOffsetNormal = m_bufferOffsetTexCoord + 2 * sizeof(GLfloat);
        m_bufferTupleSize = m_bufferOffsetNormal + 3 * sizeof(GLfloat);
    }
}

void Renderer::render()
{
    if( ! m_initialized ){
        initializeOpenGLFunctions();
        m_initialized = true;
    }

    createShaderProgram();

    updateTexture();
    createBufferObject();
    calculateMvpMatrix();
    calculateLightingMatrix();

    QSize viewportSize = window()->size() * window()->devicePixelRatio();
    glViewport(0, 0, viewportSize.width(), viewportSize.height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    draw();

    window()->resetOpenGLState();
}

void Renderer::draw()
{
    QMatrix3x3 normalMatrix = m_mvMatrix.normalMatrix();
    QMatrix4x4 lightTransformation;
    lightTransformation.rotate(m_lightAngle, 0, 1, 0);
    QVector3D lightPosition = lightTransformation * QVector3D(0,1,1);

    m_program->bind();
    if( m_texture ){
        m_texture->bind();
    }

    m_program->setUniformValue("useTexture", m_useTexture);
    m_program->setUniformValue("useLight", m_useLight);

    m_program->setUniformValue("mvpMatrix", m_mvpMatrix);

    m_program->setUniformValue("texture", 0);

    m_program->setUniformValue("mvMatrix", m_mvMatrix);
    m_program->setUniformValue("normalMatrix", normalMatrix);
    m_program->setUniformValue("lightPosition", m_vLightingMatrix * lightPosition);
    m_program->setUniformValue("ambientColor", QColor(64, 64, 64));
    m_program->setUniformValue("diffuseColor", QColor(192, 192, 196));
    m_program->setUniformValue("specularColor", QColor(255, 255, 255));
    m_program->setUniformValue("ambientReflection", (GLfloat) 1.0);
    m_program->setUniformValue("diffuseReflection", (GLfloat) 1.0);
    m_program->setUniformValue("specularReflection", (GLfloat) 1.0);
    m_program->setUniformValue("shininess", (GLfloat) 100.0);

    m_program->enableAttributeArray("vertex");
    m_program->enableAttributeArray("color");
    m_program->enableAttributeArray("textureCoordinate");
    m_program->enableAttributeArray("normal");

    if( m_useBuffer ){
        m_buffer->bind();
        m_program->setAttributeBuffer("vertex", GL_FLOAT, m_bufferOffsetVertex, 3, m_bufferTupleSize);
        m_program->setAttributeBuffer("color", GL_FLOAT, m_bufferOffsetColor, 3, m_bufferTupleSize);
        m_program->setAttributeBuffer("textureCoordinate", GL_FLOAT, m_bufferOffsetTexCoord, 2, m_bufferTupleSize);
        m_program->setAttributeBuffer("normal", GL_FLOAT, m_bufferOffsetNormal, 3, m_bufferTupleSize);
    }
    else{
        m_program->setAttributeArray("vertex", GL_FLOAT, m_arrayVertex.constData(), 3);
        m_program->setAttributeArray("color", GL_FLOAT, m_arrayColor.constData(), 3);
        m_program->setAttributeArray("textureCoordinate", GL_FLOAT, m_arrayTexCoord.constData(), 2);
        m_program->setAttributeArray("normal", GL_FLOAT, m_arrayNormal.constData(), 3);
    }

    glDrawArrays(GL_TRIANGLES, 0, m_arrayVertex.size());

    m_program->disableAttributeArray("vertex");
    m_program->disableAttributeArray("color");
    m_program->disableAttributeArray("textureCoordinate");
    m_program->disableAttributeArray("normal");
    m_program->release();
    if( m_texture ){
        m_texture->release();
    }
    if( m_useBuffer ){
        m_buffer->release();
    }
}

void Renderer::lifeGameChanged()
{
    m_updateTexture = true;
    if( window() != nullptr ){
        window()->update();
    }
}

void Renderer::mousePressed( int x, int y )
{
    m_lastMousePosition = QPoint( x, y );
}

void Renderer::mouseMoved( int x, int y, bool leftButton )
{
    if( leftButton ){
        int deltaX = x - m_lastMousePosition.x();
        int deltaY = y - m_lastMousePosition.y();

        QMatrix4x4 m;
        m.rotate( deltaX, 0, 1, 0 );
        m.rotate( deltaY, 1, 0, 0 );
        m_rotationMatrix = m * m_rotationMatrix;

        m_lastMousePosition = QPoint( x, y );

        if (window()){
            window()->update();
        }

    }
}

void Renderer::mouseReleased( int x, int y, bool leftButton )
{
}

void Renderer::pinched( double scale )
{
    if( scale != 0.0 ){
        m_distance /= scale;
    }
    if (window()){
        window()->update();
    }
}
