#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T23:02:52
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = PM_Defender
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    window.cpp \

HEADERS  += \
    widget.h \
    window.h \
    pmavmodules.h

FORMS    += widget.ui \
