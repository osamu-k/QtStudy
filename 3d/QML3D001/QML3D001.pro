QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    renderer.cpp \
    lifegame.cpp

RESOURCES += qml.qrc \
    gl.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    renderer.h \
    lifegame.h

DISTFILES += \
    textureshader.vert \
    lightingshader.vert \
    lightingshader.frag
