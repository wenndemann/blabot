#ifndef TCPIP_H
#define TCPIP_H

#include <QObject>

#include <QMessageBox>
#include <QString>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <cerrno>

class MainWindow;

class TCPIP : public QObject
{
    Q_OBJECT
public:
    explicit TCPIP(QObject *parent = 0);
    void connect(const QString& ip, int port, MainWindow *mainWindow);
    void disconnect();

    void getMeasuringIntervalMs();
    void setMeasuringIntervalMs(u_int16_t val);

signals:
    
public slots:

private:
    int m_fd;
    bool m_isConnected;
    static void* tcp_parse(void* arg);
};

#endif // TCPIP_H