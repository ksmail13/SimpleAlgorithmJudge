#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T14:48:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prac3
TEMPLATE = app


SOURCES += main.cpp\
    loginwidget.cpp \
    loginwindow.cpp \
    mainwidget.cpp \
    socketmanager.cpp \
    BasicSocket.cc \
    jsoncpp.cpp

HEADERS  += \
    loginwidget.h \
    loginwindow.h \
    mainwidget.h \
    InetSocket.h \
    BasicSocket.h \
    socketmanager.h \
    logger.h \
    json-forwards.h \
    json.h

FORMS    += \
    loginwindow.ui
