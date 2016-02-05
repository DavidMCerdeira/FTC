TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    server.cpp \
    client_connection.cpp \
    request_handler.cpp \
    ftc_error.cpp

HEADERS += \
    server.h \
    client_connection.h \
    request_handler.h \
    ftc_error.h


