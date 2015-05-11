#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:02:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BroadcastServer001
TEMPLATE = app


SOURCES += main.cpp\
        serverwidget.cpp

HEADERS  += serverwidget.h

FORMS    += serverwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib001/release/ -lBroadcastLib001
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BroadcastLib001/debug/ -lBroadcastLib001
else:unix: LIBS += -L$$OUT_PWD/../BroadcastLib001/ -lBroadcastLib001

INCLUDEPATH += $$PWD/../BroadcastLib001
DEPENDPATH += $$PWD/../BroadcastLib001

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib001/release/libBroadcastLib001.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib001/debug/libBroadcastLib001.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib001/release/BroadcastLib001.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib001/debug/BroadcastLib001.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../BroadcastLib001/libBroadcastLib001.a
