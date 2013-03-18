#ifndef DEFS_H
#define DEFS_H

#include <string>

#define BB_TCPIP_PORT 6665
#define BB_TCPIP_MSG_LENGTH 256

#define BB_PLOT_NCURVES 10
#define BB_PLOT_DATA_LENGTH 100000
#define BB_PLOT_READ_FPS 100
#define BB_PLOT_REPLOT_FPS 30

// TCP/IP DEFINES
// SC = server -> client
// CS = client -> server
#define TCP_PORT_GUI 6665
#define TCP_CMD_SENSOR_DATA_SC 0x00
#define TCP_CMD_SENSOR_INTERVAL_SC 0x02
#define TCP_CMD_SENSOR_INTERVAL_CS 0x03

class MainWindow;
class PlotManager;

struct tcpData_s {
    int sockfd;

    MainWindow *mainWindow;
    std::string name;

    tcpData_s() {}

    tcpData_s(int newsock, MainWindow *mw)
    {
        sockfd = newsock;
        mainWindow = mw;
    }
};

struct sensorData_s {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t mag[3];
    int8_t poti;
};

#endif // DEFS_H
