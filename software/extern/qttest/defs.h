#ifndef DEFS_H
#define DEFS_H

#include <string>

#define BB_TCPIP_PORT 6665
#define BB_TCPIP_MSG_LENGTH 256

#define BB_PLOT_NCURVES 3
#define BB_PLOT_DATA_LENGTH 200
#define BB_PLOT_READ_FPS 100
#define BB_PLOT_REPLOT_FPS 30

struct tcp_data {
    int newsockfd;
    std::string name;

    tcp_data() {}

    tcp_data(int newsock)
    {
        newsockfd = newsock;
    }
};

struct sensorData_s {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t mag[3];
    int8_t poti;
};

#endif // DEFS_H
