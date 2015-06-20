#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T22:02:24
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_calclib011test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_calclib011test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib011/release/ -lCalcLib011
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib011/debug/ -lCalcLib011
else:unix: LIBS += -L$$OUT_PWD/../CalcLib011/ -lCalcLib011

INCLUDEPATH += $$PWD/../CalcLib011
DEPENDPATH += $$PWD/../CalcLib011

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib011/release/libCalcLib011.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib011/debug/libCalcLib011.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib011/release/CalcLib011.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib011/debug/CalcLib011.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib011/libCalcLib011.a
