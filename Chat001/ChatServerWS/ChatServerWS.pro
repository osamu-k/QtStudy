#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T23:36:29
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServerWS
TEMPLATE = app


SOURCES += main.cpp\
    chatserverws.cpp \
    chatserverwswidget.cpp

HEADERS  += \
    chatserverws.h \
    chatserverwswidget.h

CONFIG += mobility
MOBILITY = 


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ChatLibrary/release/ -lChatLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ChatLibrary/debug/ -lChatLibrary
else:unix: LIBS += -L$$OUT_PWD/../ChatLibrary/ -lChatLibrary

INCLUDEPATH += $$PWD/../ChatLibrary
DEPENDPATH += $$PWD/../ChatLibrary

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibrary/release/libChatLibrary.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibrary/debug/libChatLibrary.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibrary/release/ChatLibrary.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ChatLibrary/debug/ChatLibrary.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ChatLibrary/libChatLibrary.a
