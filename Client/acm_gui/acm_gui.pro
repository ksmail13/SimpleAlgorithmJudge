#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T14:48:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prac3
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
    socketmanager.cpp \
    jsoncpp.cpp \
    BasicSocket.cpp \
    InetSocket.cpp \
    Thread.cpp \
    MainWindow.cpp \
    SubmitWidget.cpp \
    LoginWidget.cpp \
    ReadThread.cpp

HEADERS  += \
    InetSocket.h \
    BasicSocket.h \
    socketmanager.h \
    logger.h \
    json-forwards.h \
    json.h \
    Thread.h \
    MainWindow.h \
    SubmitWidget.h \
    LoginWidget.h \
    ReadThread.h

FORMS    += \
    loginwindow.ui
