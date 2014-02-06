#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T18:48:47
#
#-------------------------------------------------

QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttest
TEMPLATE = app

DEFINES += QWT_DLL
DEFINES += QT_DLL

win32{

    INCLUDEPATH += C:/Qt/qwt-6.1.0/src/
    CONFIG(release) {
        LIBS += -LC:/Qt/qwt-6.1.0/lib -lqwt
    } else {
        LIBS += -LC:/Qt/qwt-6.1.0/lib -lqwtd
    }
    DEPENDPATH += C:/Qt/qwt-6.1.0/src/

    INCLUDEPATH += C:/Libs/boost_1_55_0
    LIBS += -LC:/Libs/boost_1_55_0/lib32-msvc-10.0
    DEPENDPATH += C:/Libs/boost_1_55_0
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
