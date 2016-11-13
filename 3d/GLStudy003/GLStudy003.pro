QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    glview.cpp \
    cvopenglfunctions.cpp \
    cvopenglvertexbuffer.cpp \
    cvopenglshaderprogram.cpp \
    cvopenglrenderer.cpp \
    globject.cpp \
    globjecttriangle.cpp \
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
    cvopenglfunctions.h \
    cvopenglvertexbuffer.h \
    common.h \
    cvopenglshaderprogram.h \
    cvopenglrenderer.h \
    globject.h \
    globjecttriangle.h \
    globjectcube.h
