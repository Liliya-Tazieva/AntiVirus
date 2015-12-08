#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T01:46:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rtp_new
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ask_window.cpp

HEADERS  += widget.h \
    ask_window.h \
    registry.h

FORMS    += widget.ui

LIBS += -ladvapi32
