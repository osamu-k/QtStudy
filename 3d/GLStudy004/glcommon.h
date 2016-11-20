#ifndef GLCOMMON_H
#define GLCOMMON_H

#include <QVector3D>
#include <QVector4D>

//struct GlLight {
//    QVector3D position;  // in world space.
//    QVector4D ambient;
//    QVector4D diffuse;
//    QVector4D specular;
//    bool spotEnabled;
//    QVector3D spotDirection;
//    float spotCutOff;
//    float spotExponent;
//    bool attenuationEnabled;
//    QVector3D attenuationFactor;
//};

struct GlLight {
    QVector3D position;  // in world space.
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    bool spotEnabled;
    QVector3D spotDirection;
    float spotCutOff;
    float spotExponent;
    bool attenuationEnabled;
    QVector3D attenuationFactor;
};

//struct GlMaterial {
////    QVector4D ambient;
////    QVector4D diffuse;
//    QVector4D specular;
//    float shininess;
//};
struct GlMaterial {
//    QVector4D ambient;
//    QVector4D diffuse;
    QVector3D specular;
    float shininess;
};

#endif // GLCOMMON_H
