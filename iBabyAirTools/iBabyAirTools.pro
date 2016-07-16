#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T20:10:44
#
#-------------------------------------------------

QT       += core gui
QT += network

LIBS += -lws2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iBabyAirTools
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    ibabydefine.h

FORMS    += widget.ui

