#ifndef TCPIP_H
#define TCPIP_H

#include <QObject>

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


class TCPIP : public QObject
{
    Q_OBJECT
public:
    explicit TCPIP(QObject *parent = 0);
    
signals:
    
public slots:
    //void createConnection(std::string strIp, int iPort);
    void createConnection();

private:

    
};

#endif // TCPIP_H
