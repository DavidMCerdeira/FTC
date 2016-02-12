TEMPLATE = app

QT += qml quick
QT += widgets
QT += core gui qml quick
LIBS += -lrt
LIBS += -lpthread
LIBS += -lopencv_highgui
LIBS += -lopencv_core
LIBS += -lopencv_imgproc

CONFIG += c++11

SOURCES += main.cpp \
    servercon.cpp \
    usermessages.cpp \
    controller.cpp \
    login.cpp \
    ftc.cpp \
    rgbled.cpp \
    distancesensor.cpp \
    imgcapturer.cpp \
    mymessagequeue.cpp \
    mysemaphore.cpp \
    usrinfo.cpp \
    departmentsmodel.cpp \
    jobsmodel.cpp \
    searchresultmodel.cpp \
    setnameforsearch.cpp \
    camcap.cpp

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
    ftc.h \
    rgbled.h \
    distancesensor.h \
    imgcapturer.h \
    mymessagequeue.h \
    mysemaphore.h \
    usrinfo.h \
    departmentsmodel.h \
    jobsmodel.h \
    searchresultmodel.h \
    setnameforsearch.h \
    camcap.h
