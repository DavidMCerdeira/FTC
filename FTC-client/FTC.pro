TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    servercon.cpp \
    usermessages.cpp \
    controller.cpp \
    login.cpp \
    searchemployeeresultmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    servercon.h \
    usermessages.h \
    controller.h \
    login.h \
    searchemployeeresultmodel.h
