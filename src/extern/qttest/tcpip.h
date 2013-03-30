#ifndef TCPIP_H
#define TCPIP_H

#include <QObject>

#include <QMessageBox>
#include <QString>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
//#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <cerrno>
#endif

#include <boost/thread.hpp>
#include <boost/cstdint.hpp>

#include "defs.h"

class MainWindow;

class TCPIP : public QObject
{
    Q_OBJECT
public:
    explicit TCPIP(QObject *parent = 0);
    void connect(const QString& ip, int port, MainWindow *mainWindow);
    void disconnect();

    void getMeasuringIntervalMs();
    void setMeasuringIntervalMs(uint16_t val);

public slots:

private:
    int m_fd;
    bool m_isConnected;
    static void tcp_parse(const tcpData_s& tcpData);
};

#endif // TCPIP_H
