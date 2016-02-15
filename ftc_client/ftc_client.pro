TEMPLATE = app

QT += qml quick
LIBS += -lpthread
LIBS += -lrt
LIBS += -lopencv_highgui
LIBS += -lopencv_core
LIBS += -lopencv_imgproc

CONFIG += c++11

SOURCES += main.cpp \
    camcap.cpp \
    controller.cpp \
    departmentsmodel.cpp \
    distancesensor.cpp \
    ftc.cpp \
    ftc_frame.cpp \
    imgcapturer.cpp \
    jobsmodel.cpp \
    jsoncpp.cpp \
    login.cpp \
    mymessagequeue.cpp \
    mysemaphore.cpp \
    request_manager.cpp \
    rgbled.cpp \
    searchresultmodel.cpp \
    servercon.cpp \
    setnameforsearch.cpp \
    usermessages.cpp \
    usrinfo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    ftc_client.pro.user \
    DateTime.qml \
    Frame.qml \
    Home.qml \
    Keyboard.qml \
    Login.qml \
    MyButton.qml \
    MyComboBox.qml \
    MyTextHolder.qml \
    PersonalInfo.qml \
    Search.qml \
    SearchFilters.qml \
    SearchResults.qml \
    SwipeDetect.qml \
    Triangle.qml \
    virtualKeyboard.qml

HEADERS += \
    camcap.h \
    controller.h \
    departmentsmodel.h \
    distancesensor.h \
    ftc.h \
    ftc_frame.h \
    imgcapturer.h \
    jobsmodel.h \
    login.h \
    mymessagequeue.h \
    mysemaphore.h \
    request_manager.h \
    rgbled.h \
    searchresultmodel.h \
    servercon.h \
    setnameforsearch.h \
    usermessages.h \
    usrinfo.h \
    ftc_requests.h
