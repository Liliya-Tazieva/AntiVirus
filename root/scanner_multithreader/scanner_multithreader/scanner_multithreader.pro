#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T00:42:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scanner_multithreader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    emitter.h \
    worker.h \
    traverser.h

FORMS    += mainwindow.ui
