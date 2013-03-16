#include "tcpip.h"

#include "defs.h"

#define BB_NUM_THREADS 8
#define BB_NUMPOINTS 100

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t pthreadTcpIp;
sensorData_s sensorData;

void* tcp_parse(void* arg);

TCPIP::TCPIP(QObject *parent) :
    QObject(parent)
{
}

void TCPIP::connect(const QString& ip, int port, PlotManager *plotManager)
{
    if(!m_isConnected) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serv_addr;
        struct hostent *server;
        tcpData_s tcpData(sockfd, plotManager);
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
        if (pthread_create(&pthreadTcpIp, NULL, tcp_parse, &tcpData))
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

void* tcp_parse(void* arg)
{
    // TCP IP CONNECTION
    int n;
    tcpData_s tcpData = *((tcpData_s*) arg);
    do
    {
        n = read(tcpData.sockfd,(void*) &sensorData, sizeof(sensorData));
        if (n < 0)
        {
            if(errno == 9) break;
            else {
                printf("errorno %d\n", errno);
                perror("ERROR reading from socket");
                return NULL;
            }
        }
        tcpData.plotManager->addNewValue(0,sensorData.accel[0]);
        tcpData.plotManager->addNewValue(1,sensorData.accel[1]);
        tcpData.plotManager->addNewValue(2,sensorData.accel[2]);
        tcpData.plotManager->addNewValue(3,sensorData.gyro[0]);
        tcpData.plotManager->addNewValue(4,sensorData.gyro[1]);
        tcpData.plotManager->addNewValue(5,sensorData.gyro[2]);
        tcpData.plotManager->addNewValue(6,sensorData.mag[0]);
        tcpData.plotManager->addNewValue(7,sensorData.mag[1]);
        tcpData.plotManager->addNewValue(8,sensorData.mag[2]);
        tcpData.plotManager->addNewValue(9,sensorData.poti); //TODO
    } while(n >= 0);
    return NULL;
}
