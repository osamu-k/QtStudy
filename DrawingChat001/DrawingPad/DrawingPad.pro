#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T23:14:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawingPad
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

SOURCES += main.cpp\
    drawingpad.cpp \
    freehand.cpp \
    shape.cpp \
    rectangle.cpp \
    mainwidget.cpp \
    shapemaker.cpp \
    freehandmaker.cpp \
    rectanglemaker.cpp \
    drawingmodel.cpp \
    shapehandler.cpp \
    shapepainter.cpp \
    freehandpainter.cpp \
    rectanglepainter.cpp \
    shapewriter.cpp \
    drawingserver.cpp \
    image.cpp \
    imagepainter.cpp \
    shapemanipulator.cpp \
    imagemanipulator.cpp \
    drawingview.cpp

HEADERS  += drawingpad.h \
    freehand.h \
    shape.h \
    rectangle.h \
    mainwidget.h \
    shapemaker.h \
    freehandmaker.h \
    rectanglemaker.h \
    drawingmodel.h \
    shapehandler.h \
    shapepainter.h \
    freehandpainter.h \
    rectanglepainter.h \
    shapetypes.h \
    shapewriter.h \
    drawingserver.h \
    image.h \
    imagepainter.h \
    shapemanipulator.h \
    imagemanipulator.h \
    drawingview.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib/release/ -lBroadcastLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib/debug/ -lBroadcastLib
else:unix: LIBS += -L$$OUT_PWD/../BroadcastLib/ -lBroadcastLib

INCLUDEPATH += $$PWD/../BroadcastLib
DEPENDPATH += $$PWD/../BroadcastLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib/release/libBroadcastLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib/debug/libBroadcastLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib/release/BroadcastLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib/debug/BroadcastLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib/libBroadcastLib.a
