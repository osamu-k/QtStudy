#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T22:00:21
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_exprlibctest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_exprlibctest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExprLibC/release/ -lExprLibC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExprLibC/debug/ -lExprLibC
else:unix: LIBS += -L$$OUT_PWD/../ExprLibC/ -lExprLibC

INCLUDEPATH += $$PWD/../ExprLibC
DEPENDPATH += $$PWD/../ExprLibC

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibC/release/libExprLibC.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibC/debug/libExprLibC.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibC/release/ExprLibC.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibC/debug/ExprLibC.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ExprLibC/libExprLibC.a
