#include "tcpip.h"

#include "defs.h"

#include "mainwindow.h"

#define BB_NUM_THREADS 8
#define BB_NUMPOINTS 100

typedef  void* (TCPIP::*Thread2Ptr)(void*);
typedef  void* (*PthreadPtr)(void*);

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t pthreadTcpIp;
sensorData_s sensorData;

void* tcp_parse(void* arg);

TCPIP::TCPIP(QObject *parent) :
    QObject(parent)
{
}

void TCPIP::connect(const QString& ip, int port, MainWindow *mainWindow)
{
    if(!m_isConnected) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serv_addr;
        struct hostent *server;
        tcpData_s tcpData(sockfd, mainWindow);
        if (sockfd < 0)
        {
            perror("ERROR opening socket");
            return;
        }
        server = gethostbyname(ip.toAscii());
        if (server == NULL)
        {
            perror("ERROR, no such host\n");
            return;
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
        serv_addr.sin_port = htons(port);

        if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        {
            QMessageBox msgBox;
            msgBox.setText(strerror(errno));
            msgBox.setWindowTitle("TCP/IP connection error");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
        m_fd = sockfd;
        m_isConnected = true;
        Thread2Ptr t = &TCPIP::tcp_parse;
        PthreadPtr p = *(PthreadPtr*)&t;
        if (pthread_create(&pthreadTcpIp, NULL, p, &tcpData))
        {
            perror("Failed to create thread for TCP/IP parsing");

            return;
        }
    }
}

void TCPIP::disconnect() {
    close(m_fd);
    m_isConnected = false;
}

void* TCPIP::tcp_parse(void* arg)
{
    // TCP IP CONNECTION
    int n;
    int16_t tempInt;
    uint8_t buf[BB_TCPIP_MSG_LENGTH];
    tcpData_s tcpData = *((tcpData_s*) arg);
    do
    {
        n = read(tcpData.sockfd,(void*) &buf, BB_TCPIP_MSG_LENGTH);
        if (n < 0)
        {
            if(errno == EBADF) break;
            else {
                printf("errorno %d\n", errno);
                perror("ERROR reading from socket");
                return NULL;
            }
        }
        switch(buf[0]) {
            case TCP_CMD_SENSOR_DATA_SC: {
                memcpy(&sensorData, &buf[1], sizeof(sensorData));
                PlotManager *pM = tcpData.mainWindow->getPlotManagerPtr();
                pM->addNewValue(0,sensorData.accel[0]);
                pM->addNewValue(1,sensorData.accel[1]);
                pM->addNewValue(2,sensorData.accel[2]);
                pM->addNewValue(3,sensorData.gyro[0]);
                pM->addNewValue(4,sensorData.gyro[1]);
                pM->addNewValue(5,sensorData.gyro[2]);
                pM->addNewValue(6,sensorData.mag[0]);
                pM->addNewValue(7,sensorData.mag[1]);
                pM->addNewValue(8,sensorData.mag[2]);
                pM->addNewValue(9,sensorData.poti); //TODO
                break;
            }
            case TCP_CMD_SENSOR_INTERVAL_SC: {
                memcpy(&tempInt, &buf[1], sizeof(tempInt));
                QMetaObject::invokeMethod(tcpData.mainWindow, SLOT(tcpIpGetMeasuringInterval(u_int16_t)), Qt::QueuedConnection, Q_ARG(u_int16_t, tempInt));
                break;
            }
            default: {
                break;
            }
        }

    } while(n >= 0);
    return NULL;
}

void TCPIP::getMeasuringIntervalMs() {
    int n = 0;
    u_int8_t buf[4];
    buf[0] = TCP_CMD_SENSOR_INTERVAL_SC;
    buf[4] = '\0';
    n = write(m_fd, &buf, 4);
    if (n < 0) perror("ERROR writing to socket: ");
}

void TCPIP::setMeasuringIntervalMs(u_int16_t val) {
    int n = 0;
    u_int8_t buf[4];
    buf[0] = TCP_CMD_SENSOR_INTERVAL_CS;
    memcpy(&buf[1], &val, sizeof(val));
    buf[4] = '\0';
    n = write(m_fd, &buf, 4);
    if (n < 0) perror("ERROR writing to socket: ");
}

