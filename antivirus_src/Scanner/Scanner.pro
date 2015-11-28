#-------------------------------------------------
#
# Project created by QtCreator 2015-11-25T18:13:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    emitter.h \
    traverser.h \
    worker.h \
    heuristicable.h

FORMS    += mainwindow.ui

