TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread \
        -lmysqlclient

SOURCES += main.cpp \
    server.cpp \
    client_connection.cpp \
    ftc_error.cpp \
    ftc_frame.cpp \
    handler_factory.cpp \
    request_manager.cpp \
    request_handler.cpp \
    jsoncpp.cpp \
    db_accesser.cpp

HEADERS += \
    server.h \
    client_connection.h \
    ftc_error.h \
    ftc_frame.h \
    handler_factory.h \
    request_manager.h \
    request_handler.h \
    json/json-forwards.h \
    json/json.h \
    db_accesser.h


