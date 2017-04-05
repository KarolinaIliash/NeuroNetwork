#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    neuronetwork.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    neuronetwork.h

FORMS    += mainwindow.ui
