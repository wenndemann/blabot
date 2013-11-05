#ifndef DEFS_H
#define DEFS_H

#include <string>
#include <math.h>
#include <boost/cstdint.hpp>

#define BB_TCPIP_PORT 6665
#define BB_TCPIP_MSG_LENGTH 1024

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

namespace SensorData
{
    struct vectorInt16
    {
        vectorInt16() {x = y = z = 0;}
        vectorInt16(int16_t X, int16_t Y, int16_t Z) {x=X;y=Y;z=Z;}
        void set(int16_t X, int16_t Y, int16_t Z) {x=X;y=Y;z=Z;}
        int16_t x, y, z;
    };

    struct vector
    {
        vector() {x = y = z = 0.0f;}
        vector(float X, float Y, float Z) {x=X;y=Y;z=Z;}
        vector(const vectorInt16 &v16) {
            x = static_cast<float>(v16.x);
            y = static_cast<float>(v16.y);
            z = static_cast<float>(v16.z);
        }
        void set(float X, float Y, float Z) {x=X;y=Y;z=Z;}
        void set(int16_t X, int16_t Y, int16_t Z) {
            x = static_cast<float>(X);
            y = static_cast<float>(Y);
            z = static_cast<float>(Z);
        }

        float x, y, z;

        static float dot(const vector& a,const vector& b)
        {
          return a.x*b.x+a.y*b.y+a.z*b.z;
        }

        static void normalize(vector& v)
        {
            float mag = sqrt(dot(v,v));
            v.x /= mag;
            v.y /= mag;
            v.z /= mag;
        }

        static void cross(const vector& vecA, const vector& vecB, vector& vecDest)
        {
            vecDest.x = vecA.y * vecB.z - vecA.z * vecB.y;
            vecDest.y = vecA.z * vecB.x - vecA.x * vecB.z;
            vecDest.z = vecA.x * vecB.y - vecA.y * vecB.x;
        }
    };

    struct sensorData_s {
        vectorInt16 accRaw;
        vector acc;
        vectorInt16 gyroRaw;
        vector gyro;
        vectorInt16 magRaw;
        vector mag;
        int8_t poti;
    };
} // namespace SensorData

#endif // DEFS_H
