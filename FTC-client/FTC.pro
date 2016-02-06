TEMPLATE = app

QT += qml quick
QT += widgets
QT += core gui qml quick
LIBS += -lrt
LIBS += -lpthread

CONFIG += c++11

SOURCES += main.cpp \
    servercon.cpp \
    usermessages.cpp \
    controller.cpp \
    login.cpp \
    searchemployeeresultmodel.cpp \
    searchworkingmodel.cpp \
    departmentmodel.cpp \
    ftc.cpp \
    rgbled.cpp \
    distancesensor.cpp \
    imgcapturer.cpp \
    mymessagequeue.cpp \
    mysemaphore.cpp \
    usrinfo.cpp

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
    searchemployeeresultmodel.h \
    searchworkingmodel.h \
    departmentmodel.h \
    ftc.h \
    rgbled.h \
    distancesensor.h \
    imgcapturer.h \
    mymessagequeue.h \
    mysemaphore.h \
    usrinfo.h
