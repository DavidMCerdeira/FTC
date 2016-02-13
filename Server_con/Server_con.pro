TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ftc_frame.cpp \
    jsoncpp.cpp \
    servercon.cpp \
    usrinfo.cpp \
    server_connection.cpp \
    request_manager.cpp

HEADERS += \
    servercon.h \
    ftc_frame.h \
    json/json.h \
    json/json-forwards.h \
    server_connection.h \
    request_manager.h
