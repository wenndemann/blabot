
#include <string>

#define SEMM_TCPIP_PORT 6665
#define SEMM_MSG_LENGTH 256

#define ACCEL_ADDR 0x53
#define ACCEL_POWER_CTL 0x2d
#define ACCEL_DATA_FORMAT 0x31
#define ACCEL_X 0x32
#define ACCEL_Y 0x34
#define ACCEL_Z 0x36

#define GYRO_ADDR 0x68
#define GYRO_POWER_CTL	0x3e
#define GYRO_DLPF_FS	0x16
#define GYRO_X 0x1d
#define GYRO_Y 0x1f
#define GYRO_Z 0x21


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
	uint16_t enable;	
};


