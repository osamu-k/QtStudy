#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T06:12:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = ExprLibCpp3
TEMPLATE = lib
CONFIG += staticlib

SOURCES += evaluator.cpp \
    interpreter.cpp \
    parser.cpp \
    syntaxnode.cpp \
    tokenizer.cpp \
    tree.cpp \
    treeiterator.cpp

HEADERS += evaluator.h \
    interpreter.h \
    nodevisitor.h \
    parser.h \
    syntaxnode.h \
    token.h \
    tokenizer.h \
    tree.h \
    treeiterator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
