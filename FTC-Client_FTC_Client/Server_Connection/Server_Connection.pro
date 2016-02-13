TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    ftc_frame.cpp \
    jsoncpp.cpp \
    request_manager.cpp \
    server_connection.cpp

HEADERS += \
    ftc_frame.h \
    request_manager.h \
    server_connection.h
