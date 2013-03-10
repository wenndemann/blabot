#ifndef DEFS_H
#define DEFS_H

#include <string>
#include "plotmanager.h"

#define BB_TCPIP_PORT 6665
#define BB_TCPIP_MSG_LENGTH 256

#define BB_PLOT_NCURVES 10
#define BB_PLOT_DATA_LENGTH 200
#define BB_PLOT_READ_FPS 100
#define BB_PLOT_REPLOT_FPS 30


struct lala {
    PlotManager b;
};

struct tcpData_s {
    int sockfd;
    std::string name;

    tcpData_s() {}

    tcpData_s(int newsock)
    {
        sockfd = newsock;
    }
};

struct sensorData_s {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t mag[3];
    int8_t poti;
};

#endif // DEFS_H
