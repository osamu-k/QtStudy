#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QQuickItem>
#include <QQuickWindow>

#include "lifegame.h"

class Renderer : public QQuickItem, private QOpenGLFunctions
{
    Q_OBJECT

//    Q_PROPERTY(double alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)
//    Q_PROPERTY(double beta READ beta WRITE setBeta NOTIFY betaChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(double lightAngle READ lightAngle WRITE setLightAngle NOTIFY lightAngleChanged)

    Q_PROPERTY(bool useTexture READ useTexture WRITE setUseTexture NOTIFY useTextureChanged)
    Q_PROPERTY(bool useLight READ useLight WRITE setUseLight NOTIFY useLightChanged)
    Q_PROPERTY(bool useBuffer READ useBuffer WRITE setUseBuffer NOTIFY useBufferChanged)
public:
    explicit Renderer(QQuickItem *parent = 0);
    ~Renderer();

//    void setAlpha( double value );
//    double alpha() const;

//    void setBeta( double value );
//    double beta() const;

    void setDistance( double value );
    double distance() const;

    void setLightAngle( double value );
    double lightAngle() const;

    void setUseTexture( bool value );
    bool useTexture() const;

    void setUseLight( bool value );
    bool useLight() const;

    void setUseBuffer( bool value );
    bool useBuffer() const;

signals:
    void alphaChanged( double value );
    void betaChanged( double value );
    void distanceChanged( double value );
    void lightAngleChanged( double value );
    void useTextureChanged( bool value );
    void useLightChanged( bool value );
    void useBufferChanged( bool value );

public slots:
    void mousePressed( int x, int y );
    void mouseMoved( int x, int y, bool leftButton );
    void mouseReleased( int x, int y, bool leftButton );
    void pinched(  double scale  );

private slots:
    void handleWindowChange(QQuickWindow *window);
    void render();
    void lifeGameChanged();

private:
    static const int NUM_VERTICES = 8;
    static const int NUM_FACES = 6;

    static QVector3D m_cubeVertices[NUM_VERTICES];
    static GLubyte m_cubeVertexIndices[NUM_FACES * 6];
    static QVector3D m_cubeColors[NUM_FACES];
    static QVector2D m_textureCoordinates[6];

//    double m_alpha;
//    double m_beta;
    QMatrix4x4 m_rotationMatrix;
    double m_distance;
    double m_lightAngle;

    bool m_useTexture;
    bool m_useLight;
    bool m_useBuffer;
    bool m_initialized;

    QVector<QVector3D> m_arrayVertex;
    QVector<QVector3D> m_arrayColor;
    QVector<QVector2D> m_arrayTexCoord;
    QVector<QVector3D> m_arrayNormal;

    QOpenGLShaderProgram *m_program;
    QOpenGLTexture *m_texture;
    QOpenGLBuffer *m_buffer;

    int m_bufferOffsetVertex = 0;
    int m_bufferOffsetColor = 0;
    int m_bufferOffsetTexCoord = 0;
    int m_bufferOffsetNormal = 0;
    int m_bufferTupleSize = 0;

    QMatrix4x4 m_mMatrix;
    QMatrix4x4 m_vMatrix;
    QMatrix4x4 m_pMatrix;
    QMatrix4x4 m_mvMatrix;
    QMatrix4x4 m_mvpMatrix;

    QMatrix4x4 m_mLightingMatrix;
    QMatrix4x4 m_vLightingMatrix;
    QMatrix4x4 m_pLightingMatrix;
    QMatrix4x4 m_mvLightingMatrix;
    QMatrix4x4 m_mvpLightingMatrix;

    QVector<QVector3D> m_spotlightVertices;
    QVector<QVector3D> m_spotlightColors;

    LifeGame m_lifeGame;
    bool m_updateTexture;
    int m_cellSize;
    int m_cellCount;
    QImage m_image;

    void createArrays();
    void createArrayVertex();
    void createArrayColor();
    void createArrayTexCoord();
    void createArrayNormal();
    QVector3D createPolygonNormal( QVector3D a, QVector3D b, QVector3D c );
    void createShaderProgram();
    QImage createTextureImage();
    void updateTexture();
    void createBufferObject();
    void calculateMvpMatrix();
    void calculateLightingMatrix();
    void draw();

    QPoint m_lastMousePosition;
};

#endif // RENDERER_H
