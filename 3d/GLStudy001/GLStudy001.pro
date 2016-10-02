QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    modelrenderer.cpp

RESOURCES += qml.qrc \
    opengl.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    modelrenderer.h

DISTFILES +=
