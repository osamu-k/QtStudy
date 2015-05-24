#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T09:52:02
#
#-------------------------------------------------

QT       -= core gui

TARGET = ExprLibC
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    tokenizer.c \
    parser.c \
    evaluator.c \
    syntaxtree.c \
    interpreter.c \
    varlist.c

HEADERS += \
    tokenizer.h \
    parser.h \
    evaluator.h \
    syntaxtree.h \
    interpreter.h \
    varlist.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
