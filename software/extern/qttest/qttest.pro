#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T18:48:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttest
TEMPLATE = app

INCLUDEPATH += /usr/include/qwt

LIBS += -L/usr/lib -lqwt

DEPENDPATH += /usr/include/qwt

SOURCES += main.cpp\
        mainwindow.cpp \
    graphplotter.cpp \
    tcpip.cpp

HEADERS  += mainwindow.h \
    graphplotter.h \
    tcpip.h \
    defs.h

FORMS    += mainwindow.ui
