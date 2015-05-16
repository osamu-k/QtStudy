#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T23:14:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawingPad01
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
    imagepainter.cpp

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
    imagepainter.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/release/ -lBroadcastLib001
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/debug/ -lBroadcastLib001
else:unix: LIBS += -L$$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/ -lBroadcastLib001

INCLUDEPATH += $$PWD/../Broadcast001/BroadcastLib001
DEPENDPATH += $$PWD/../Broadcast001/BroadcastLib001

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/release/libBroadcastLib001.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/debug/libBroadcastLib001.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/release/BroadcastLib001.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/debug/BroadcastLib001.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-Broadcast001-Desktop_Qt_5_4_1_clang_64bit-Debug/BroadcastLib001/libBroadcastLib001.a
