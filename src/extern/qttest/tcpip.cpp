#include "tcpip.h"
#include "mainwindow.h"

#define BB_NUM_THREADS 8
#define BB_NUMPOINTS 100

//pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_t pthreadTcpIp;

boost::mutex g_mutex;
//boost::thread threadTcpIp;

SensorData::sensorData_s sensorData;

void* tcp_parse(void* arg);

void simpleUpdate(MainWindow* mW, float NormX, float NormY, float NormZ);

// -----------------------------------------------------------------------------
#include <math.h>

// System constants
#define deltat 0.01f // sampling period in seconds (shown as 1 ms)
#define gyroMeasError 3.14159265358979f * (50.0f / 180.0f) // gyroscope measurement error in rad/s (shown as 5 deg/s)
//#define gyroMeasError 3.14159265358979f * 0.03 * sqrt(deltat) / 180.0f // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError // compute beta

// estimated orientation quaternion elements with initial conditions
float SEq_1 = 1.0f, SEq_2 = 0.0f, SEq_3 = 0.0f, SEq_4 = 0.0f;

void filterUpdate(double w_x, double w_y, double w_z,
                  double a_x, double a_y, double a_z);
// -----------------------------------------------------------------------------

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
        server = gethostbyname(ip.toLatin1());
        if (server == NULL)
        {
            perror("ERROR, no such host\n");
            return;
        }

        //bzero((char *) &serv_addr, sizeof(serv_addr));
        memset((char *) &serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        //    server->h_length);
        memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr,
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

        //if (pthread_create(&pthreadTcpIp, NULL, &tcp_parse, &tcpData))
        //{
        //    perror("Failed to create thread for TCP/IP parsing");
        //    return;
        //}
        boost::thread threadTcpIp(tcp_parse, tcpData);

        // uncomment to wait until the thread has been closed
        //threadTcpIp.join();
    }
}

void TCPIP::disconnect() {
    _close(m_fd);
    m_isConnected = false;
}

void TCPIP::tcp_parse(const tcpData_s& tcpData)
{
    // TCP IP CONNECTION
    int n = -1;
    int16_t tempInt;
    uint8_t buf[BB_TCPIP_MSG_LENGTH];

    do
    {
        n = _read(tcpData.sockfd,(void*) &buf, BB_TCPIP_MSG_LENGTH);
        if (n < 0)
        {
            if(errno == EBADF) break;
            else {
                printf("errorno %d\n", errno);
                perror("ERROR reading from socket");
                return;
            }
        }
        switch(buf[0]) {
            case TCP_CMD_SENSOR_DATA_SC: {
                memcpy(&sensorData, &buf[1], sizeof(sensorData));

                /*
                // manual measured gyro offset
                gyro[0] -= 57.997;
                gyro[1] -= -247.446;
                gyro[2] -= -72.822;

                // translate measured values to rad / sec (sensor specific)
                for (uint8_t i = 0; i < 3; i++) {
                    gyro[i] /= 14.375; // degree / sec
                    gyro[i] = gyro[i] / 180.0 * M_PI;
                    gyro[i] /= 4.0;
                }
                */

                // save the measeured values
                PlotManager *pM = tcpData.mainWindow->getPlotManagerPtr();

                sensorData.acc = SensorData::vector(sensorData.accRaw);
                sensorData.gyro = SensorData::vector(sensorData.gyroRaw);
                sensorData.mag = SensorData::vector(sensorData.magRaw);

                SensorData::vector::normalize(sensorData.acc);
                SensorData::vector::normalize(sensorData.gyro);
                SensorData::vector::normalize(sensorData.mag);

                pM->addNewValue(0,static_cast<double>(sensorData.acc.x));
                pM->addNewValue(1,static_cast<double>(sensorData.acc.y));
                pM->addNewValue(2,static_cast<double>(sensorData.acc.z));
                pM->addNewValue(3,static_cast<double>(sensorData.gyro.x));
                pM->addNewValue(4,static_cast<double>(sensorData.gyro.y));
                pM->addNewValue(5,static_cast<double>(sensorData.gyro.z));
                pM->addNewValue(6,static_cast<double>(sensorData.mag.x));
                pM->addNewValue(7,static_cast<double>(sensorData.mag.y));
                pM->addNewValue(8,static_cast<double>(sensorData.mag.z));
                pM->addNewValue(9,static_cast<double>(sensorData.poti)); //TODO

                //filterUpdate(sensorData.gyro.x,0,0, 0, sensorData.acc.y, sensorData.acc.z);

                VisWidget *vW = tcpData.mainWindow->getWidgetVisualizationPtr();
                //vW->setQuaternions(SEq_1, SEq_2, SEq_3, SEq_4);


                //QQuaternion SEq(SEq_1, SEq_2, SEq_3, SEq_4);

                /*
                QQuaternion ESq = SEq.conjugate();
                QQuaternion ASq;
                ASq.setScalar(ESq.scalar()*ASq.scalar() - ESq.x()*ASq.x()      - ESq.y()*ASq.y()      - ESq.z()*ASq.z());
                ASq.setX     (ESq.scalar()*ASq.x()      + ESq.x()*ASq.scalar() + ESq.y()*ASq.z()      - ESq.z()*ASq.y());
                ASq.setY     (ESq.scalar()*ASq.y()      - ESq.x()*ASq.z()      + ESq.y()*ASq.scalar() + ESq.z()*ASq.x());
                ASq.setZ     (ESq.scalar()*ASq.z()      + ESq.x()*ASq.y()      - ESq.y()*ASq.x()      + ESq.z()*ASq.scalar());

                vW->setQuaternions(&ASq);
                tcpData.mainWindow->setQuaternions(&ASq);
                */
                //QQuaternion SEq(1.0, sensorData.acc.x, sensorData.acc.y, sensorData.acc.z);
                //vW->setQuaternions(&SEq);

                tcpData.mainWindow->setQuaternionVals(1.0, sensorData.acc.x, sensorData.acc.y, sensorData.acc.z);
                qDebug("sensorData: (%.1f,%.1f,%.1f)", sensorData.acc.x, sensorData.acc.y, sensorData.acc.z);

                vW->setRotation(sensorData);


                break;
            }
            case TCP_CMD_SENSOR_INTERVAL_SC: {
                memcpy(&tempInt, &buf[1], sizeof(tempInt));
                QMetaObject::invokeMethod(tcpData.mainWindow, "tcpIpGetMeasuringInterval", Qt::QueuedConnection, Q_ARG(quint16, tempInt));
                break;
            }
            default: {
                break;
            }
        }

    } while(n >= 0);
}

void TCPIP::getMeasuringIntervalMs() {
    uint8_t buf[2];
    buf[0] = TCP_CMD_SENSOR_INTERVAL_SC;
    buf[1] = '\0';
    if (_write(m_fd, &buf, 2) < 0) perror("ERROR writing to socket: ");
}

void TCPIP::setMeasuringIntervalMs(uint16_t val) {
    uint8_t buf[4];
    buf[0] = TCP_CMD_SENSOR_INTERVAL_CS;
    memcpy(&buf[1], &val, sizeof(val));
    buf[3] = '\0';
    if (_write(m_fd, &buf, 4) < 0) perror("ERROR writing to socket: ");
}

void simpleUpdate(MainWindow* mW, float NormX, float NormY, float NormZ) {
    float fNorm = sqrt(pow(double(NormX), 2.0) + pow(double(NormY), 2.0) + pow(double(NormZ), 2.0));
    float x = NormX / fNorm;
    float y = NormY / fNorm;
    float z = NormZ / fNorm;

    NormX = y * 0.0f - z * 0.0f;
    NormY = z * 1.0f - x * 0.0f;
    NormZ = x * 0.0f - y * 1.0f;

    float AngleRot = acos((x * 1.0f + y * 0.0f + z * 0.0f) /
                          (sqrt(pow(double(x), 2.0) + pow(double(y), 2.0) + pow(double(z), 2.0)) +
                           sqrt(pow(double(1.0f), 2.0) + pow(double(0.0f), 2.0) + pow(double(0.0f), 2.0))));

    AngleRot = AngleRot / M_PI * 180;


    //mW->getWidgetVisualizationPtr()->setRotation(AngleRot, NormX, NormY, NormZ);

    //mW->setQuaternionVals(AngleRot, NormX, NormY, NormZ);
}

void filterUpdate(double w_x, double w_y, double w_z, double a_x, double a_y, double a_z)
{
    // Local system variables
    float norm;
    // vector norm
    float SEqDot_omega_1, SEqDot_omega_2, SEqDot_omega_3, SEqDot_omega_4;   // quaternion derrivative from gyroscopes elements
    float f_1, f_2, f_3;                                                    // objective function elements
    float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33;               // objective function Jacobian elements
    float SEqHatDot_1, SEqHatDot_2, SEqHatDot_3, SEqHatDot_4;               // estimated direction of the gyroscope error
    // Axulirary variables to avoid reapeated calcualtions
    float halfSEq_1 = 0.5f * SEq_1;
    float halfSEq_2 = 0.5f * SEq_2;
    float halfSEq_3 = 0.5f * SEq_3;
    float halfSEq_4 = 0.5f * SEq_4;
    float twoSEq_1 = 2.0f * SEq_1;
    float twoSEq_2 = 2.0f * SEq_2;
    float twoSEq_3 = 2.0f * SEq_3;

    // Compute the quaternion derrivative measured by gyroscopes
    SEqDot_omega_1 = -halfSEq_2 * w_x - halfSEq_3 * w_y - halfSEq_4 * w_z;
    SEqDot_omega_2 = halfSEq_1 * w_x + halfSEq_3 * w_z - halfSEq_4 * w_y;
    SEqDot_omega_3 = halfSEq_1 * w_y - halfSEq_2 * w_z + halfSEq_4 * w_x;
    SEqDot_omega_4 = halfSEq_1 * w_z + halfSEq_2 * w_y - halfSEq_3 * w_x;

    // Normalise the accelerometer measurement
    norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
    a_x /= norm;
    a_y /= norm;
    a_z /= norm;

    // Compute the objective function and Jacobian
    f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - a_x;
    f_2 = 1.0 - twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - a_y;
    f_3 = twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - a_z;
    J_11or24 = twoSEq_3;                                                    // J_11 negated in matrix multiplication
    J_12or23 = 2.0f * SEq_4;
    J_13or22 = twoSEq_1;                                                    // J_12 negated in matrix multiplication
    J_14or21 = twoSEq_2;
    J_32 = 2.0f * J_14or21;                                                 // negated in matrix multiplication
    J_33 = 2.0f * J_11or24;                                                 // negated in matrix multiplication

    // Compute the gradient (matrix multiplication)
    SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1;
    SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3;
    SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1;
    SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2;

    // Normalise the gradient
    norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 + SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4);
    SEqHatDot_1 /= norm;
    SEqHatDot_2 /= norm;
    SEqHatDot_3 /= norm;
    SEqHatDot_4 /= norm;

    // Compute then integrate the estimated quaternion derrivative
    SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltat;
    SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltat;
    SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltat;
    SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltat;

    // Normalise quaternion
    norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4);
    SEq_1 /= norm;
    SEq_2 /= norm;
    SEq_3 /= norm;
    SEq_4 /= norm;
}
