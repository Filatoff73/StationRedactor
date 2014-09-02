#-------------------------------------------------
#
# Project created by QtCreator 2014-08-20T11:12:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StationRedactor
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainelement.cpp \
    blockrelay.cpp \
    contacts.cpp \
    mainwindow.cpp

HEADERS  += widget.h \
    mainelement.h \
    blockrelay.h \
    contacts.h \
    mainwindow.h \
    constans.h

FORMS    += widget.ui \
    mainwindow.ui
