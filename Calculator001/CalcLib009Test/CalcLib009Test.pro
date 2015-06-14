#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T18:10:34
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_calclib009test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_calclib009test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib009/release/ -lCalcLib009
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib009/debug/ -lCalcLib009
else:unix: LIBS += -L$$OUT_PWD/../CalcLib009/ -lCalcLib009

INCLUDEPATH += $$PWD/../CalcLib009
DEPENDPATH += $$PWD/../CalcLib009

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib009/release/libCalcLib009.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib009/debug/libCalcLib009.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib009/release/CalcLib009.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib009/debug/CalcLib009.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib009/libCalcLib009.a
