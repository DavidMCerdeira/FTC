TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    request_manager.cpp \
    request_handler.cpp \
    jsoncpp.cpp \
    handler_factory.cpp \
    ftc_frame.cpp \
    db_accesser.cpp

LIBS += -lpthread \
        -lmysqlclient

HEADERS += \
    request_manager.h \
    request_handler.h \
    handler_factory.h \
    ftc_frame.h \
    db_accesser.h
