#include "tcpip.h"

#include "defs.h"

#define BB_NUM_THREADS 8
#define BB_NUMPOINTS 100

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t g_threads[BB_NUM_THREADS];
sensorData_s sensorData;

void* tcp_parse(void* arg);

TCPIP::TCPIP(QObject *parent) :
    QObject(parent)
{
}

//void TCPIP::createConnection(std::string strIp, int iPort)
void TCPIP::connect(const QString& ip, int port, PlotManager *plotManager)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    tcpData_s tcpData(sockfd);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        return;
    }

    //server = gethostbyname(strIp.c_str()); // TODO
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

    if (pthread_create(&g_threads[0], NULL, tcp_parse, &sockfd))
    {
        perror("Failed to create thread for TCP/IP parsing");

        return;
    }

}

void* tcp_parse(void* arg)
{
    // TCP IP CONNECTION
    int n, sockfd;
    //long gyroInt = 0;
    sockfd = *((int*) arg);
    //gnuplot_ctrl *h1;
    double buf[9][BB_NUMPOINTS];

    for(int i = 0; i < 9; i++)
        bzero(buf[i], BB_NUMPOINTS);
    //h1 = gnuplot_init();
    //gnuplot_setstyle(h1, "lines");
    //gnuplot_cmd(h1, "set yrange [-550:550]");

    while(true)
    {

        n = read(sockfd,(void*) &sensorData, sizeof(sensorData));
        if (n < 0)
        {
            perror("ERROR reading from socket");
            return NULL;
        }

        fprintf(stdout, "%f\n", (double) sensorData.accel[0]);

         /*
        for(int i = 0; i < 9; i++)
            memcpy(&buf[i][0], &buf[i][1], (BB_NUMPOINTS-1) * sizeof(double));

        gyroInt += sensorData.gyro[0]>>5;


        buf[0][BB_NUMPOINTS-1] = (double) sensorData.accel[0];
        buf[1][BB_NUMPOINTS-1] = (double) sensorData.accel[1];
        buf[2][BB_NUMPOINTS-1] = (double) sensorData.accel[2];
        buf[3][BB_NUMPOINTS-1] = (double) sensorData.gyro[0];
        buf[4][BB_NUMPOINTS-1] = (double) gyroInt;
        buf[5][BB_NUMPOINTS-1] = (double) sensorData.gyro[2];
        buf[6][BB_NUMPOINTS-1] = (double) sensorData.mag[0];
        buf[7][BB_NUMPOINTS-1] = (double) sensorData.mag[1];
        buf[8][BB_NUMPOINTS-1] = (double) sensorData.mag[2];

        gyroInt += (sensorData.gyro[0]>>5)+2;

        gnuplot_resetplot(h1);
        gnuplot_cmd(h1, "set yrange [-550:550]");

        //gnuplot_plot_x(h1, buf[0], BB_NUMPOINTS, "accel_x");
        gnuplot_plot_x(h1, buf[1], BB_NUMPOINTS, "accel_y");
        gnuplot_plot_x(h1, buf[2], BB_NUMPOINTS, "accel_z");
        gnuplot_plot_x(h1, buf[3], BB_NUMPOINTS, " gyro_x");
        gnuplot_plot_x(h1, buf[4], BB_NUMPOINTS, " gyroInt");
        //gnuplot_plot_x(h1, buf[5], BB_NUMPOINTS, " gyro_z");
        //gnuplot_plot_x(h1, buf[6], BB_NUMPOINTS, "  mag_x");
        //gnuplot_plot_x(h1, buf[7], BB_NUMPOINTS, "  mag_y");
        //gnuplot_plot_x(h1, buf[8], BB_NUMPOINTS, "  mag_z");
        */

    }


    close(sockfd);

    return NULL;
}
