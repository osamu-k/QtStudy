#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T00:20:21
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_exprlibcpp3test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_exprlibcpp3test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp3/release/ -lExprLibCpp3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp3/debug/ -lExprLibCpp3
else:unix: LIBS += -L$$OUT_PWD/../ExprLibCpp3/ -lExprLibCpp3

INCLUDEPATH += $$PWD/../ExprLibCpp3
DEPENDPATH += $$PWD/../ExprLibCpp3

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/release/libExprLibCpp3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/debug/libExprLibCpp3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/release/ExprLibCpp3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/debug/ExprLibCpp3.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/libExprLibCpp3.a
