#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T21:20:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClientCpp
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp

HEADERS  += mainwidget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ChatLib/release/ -lChatLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ChatLib/debug/ -lChatLib
else:unix: LIBS += -L$$OUT_PWD/../ChatLib/ -lChatLib

INCLUDEPATH += $$PWD/../ChatLib
DEPENDPATH += $$PWD/../ChatLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/release/libChatLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/debug/libChatLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/release/ChatLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/debug/ChatLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ChatLib/libChatLib.a
