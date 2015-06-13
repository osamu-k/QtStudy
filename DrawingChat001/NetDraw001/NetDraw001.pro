#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T23:51:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetDraw001
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linewidthdialog.cpp \
    controller/drawingcontroller.cpp \
    controller/freehandmaker.cpp \
    controller/rectanglemaker.cpp \
    controller/shapemaker.cpp \
    model/drawingsettings.cpp \
    model/freehand.cpp \
    model/freehandfactory.cpp \
    model/rectangle.cpp \
    model/rectanglefactory.cpp \
    model/shape.cpp \
    model/shapefactory.cpp \
    model/shapespace.cpp \
    model/shapevisitor.cpp \
    view/drawingview.cpp \
    view/drawvisitor.cpp \
    view/scrollview.cpp \
    model/netshapespace.cpp

HEADERS  += mainwindow.h \
    linewidthdialog.h \
    controller/drawingcontroller.h \
    controller/freehandmaker.h \
    controller/rectanglemaker.h \
    controller/shapemaker.h \
    model/drawingsettings.h \
    model/freehand.h \
    model/freehandfactory.h \
    model/rectangle.h \
    model/rectanglefactory.h \
    model/shape.h \
    model/shapefactory.h \
    model/shapespace.h \
    model/shapevisitor.h \
    view/drawingview.h \
    view/drawvisitor.h \
    view/scrollview.h \
    model/netshapespace.h

INCLUDEPATH += . \
    controller \
    model \
    view

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib002/release/ -lBroadcastLib002
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib002/debug/ -lBroadcastLib002
else:unix: LIBS += -L$$OUT_PWD/../BroadcastLib002/ -lBroadcastLib002

INCLUDEPATH += $$PWD/../BroadcastLib002
DEPENDPATH += $$PWD/../BroadcastLib002

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib002/release/libBroadcastLib002.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib002/debug/libBroadcastLib002.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib002/release/BroadcastLib002.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib002/debug/BroadcastLib002.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib002/libBroadcastLib002.a
