#ifndef DEFS_H_
#define DEFS_H_

// I2C DEFINES
//#define I2C_ACCEL_ADDR 0x19
//#define I2C_ACCEL_POWER_CTL 0x2d
//#define I2C_ACCEL_DATA_FORMAT 0x31
//#define I2C_ACCEL_X 0x32
//
//#define I2C_GYRO_ADDR 0x6b
//#define I2C_GYRO_POWER_CTL	0x3e
//#define I2C_GYRO_DLPF_FS	0x16
//#define I2C_GYRO_X 0x1d
//
//#define I2C_MAG_ADDR 	0x1e
//#define I2C_MAG_MODE	  0x02
//#define I2C_MAG_X	0x03
//
//#define I2C_POTI_ADDR 0x48
//#define I2C_POTI_CTRL 0x00

// TCP/IP DEFINES
// SC = server -> client
// CS = client -> server
#define TCP_PORT_GUI 6665
#define TCP_MSG_LENGTH 256
#define TCP_CMD_SENSOR_DATA_SC 0x00
#define TCP_CMD_SENSOR_INTERVAL_SC 0x02
#define TCP_CMD_SENSOR_INTERVAL_CS 0x03


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
	LSM303::data accel;
	L3G::data gyro;
	LSM303::data mag;
	int8_t poti;
};

#endif
