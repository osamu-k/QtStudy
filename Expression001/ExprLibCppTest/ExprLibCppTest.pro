#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T09:21:25
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_exprlibcpptest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_exprlibcpptest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp/release/ -lExprLibCpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp/debug/ -lExprLibCpp
else:unix: LIBS += -L$$OUT_PWD/../ExprLibCpp/ -lExprLibCpp

INCLUDEPATH += $$PWD/../ExprLibCpp
DEPENDPATH += $$PWD/../ExprLibCpp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp/release/libExprLibCpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp/debug/libExprLibCpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp/release/ExprLibCpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp/debug/ExprLibCpp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp/libExprLibCpp.a
