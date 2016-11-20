QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    glview.cpp \
    glrenderer.cpp \
    glshaderprogram.cpp \
    glvertexbuffer.cpp \
    globject.cpp \
    globjectcube.cpp

RESOURCES += qml.qrc \
    opengl.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    glview.h \
    common.h \
    glrenderer.h \
    glshaderprogram.h \
    glcommon.h \
    glvertexbuffer.h \
    globject.h \
    globjectcube.h
