TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    db_accesser.cpp

HEADERS += \
    db_accesser.h

LIBS += -lmysqlclient
LIBS += -lpthread
