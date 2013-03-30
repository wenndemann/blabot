#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T18:48:47
#
#-------------------------------------------------

QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttest
TEMPLATE = app

win32{
    INCLUDEPATH += C:/Qt/qwt/src
    LIBS += -LC:/Qt/qwt/lib -lqwt
    DEPENDPATH += C:/Qt/qwt/src

    INCLUDEPATH += C:/boost
    LIBS += -LC:/boost/lib -llibboost_system -llibboost_thread
    DEPENDPATH += C:/boost
}
!win32{
    INCLUDEPATH += /usr/include/qwt
    LIBS += -L/usr/lib -lqwt -lboost_system -lboost_thread
    DEPENDPATH += /usr/include/qwt
}

SOURCES += main.cpp\
        mainwindow.cpp \
    graphplotter.cpp \
    tcpip.cpp \
    widgetcurvecontrol.cpp \
    plotmanager.cpp \
    viswidget.cpp

HEADERS  += mainwindow.h \
    graphplotter.h \
    tcpip.h \
    defs.h \
    widgetcurvecontrol.h \
    plotmanager.h \
    viswidget.h

FORMS += mainwindow.ui
