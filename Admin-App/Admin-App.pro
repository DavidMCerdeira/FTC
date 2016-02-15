#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T17:48:34
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
LIBS += -lpthread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Admin-App
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    register.cpp \
    terminalflow.cpp \
    searchemployee.cpp \
    sendmessage.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    register.h \
    terminalflow.h \
    searchemployee.h \
    sendmessage.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui
