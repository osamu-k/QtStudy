#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T14:13:16
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_exprlibcpp2test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_exprlibcpp2test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp2/release/ -lExprLibCpp2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp2/debug/ -lExprLibCpp2
else:unix: LIBS += -L$$OUT_PWD/../ExprLibCpp2/ -lExprLibCpp2

INCLUDEPATH += $$PWD/../ExprLibCpp2
DEPENDPATH += $$PWD/../ExprLibCpp2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp2/release/libExprLibCpp2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp2/debug/libExprLibCpp2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp2/release/ExprLibCpp2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp2/debug/ExprLibCpp2.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp2/libExprLibCpp2.a
