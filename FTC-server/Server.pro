TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -pthread

SOURCES += main.cpp \
    server.cpp \
    client_connection.cpp \
    request_handler.cpp

HEADERS += \
    server.h \
    client_connection.h \
    request_handler.h

