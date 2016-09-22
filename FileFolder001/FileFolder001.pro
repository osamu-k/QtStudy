QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    standardpaths.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    standardpaths.h \
    qtappdelegate.h

ios {
    QMAKE_INFO_PLIST = Info.plist
}

OBJECTIVE_SOURCES += \
    qtappdelegate.mm
