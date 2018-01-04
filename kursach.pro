#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T18:42:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kursach
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startup.cpp \
    history.cpp

HEADERS  += mainwindow.h \
    startup.h \
    history.h

FORMS    += mainwindow.ui \
    startup.ui \
    history.ui
