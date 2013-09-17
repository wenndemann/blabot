#ifndef DEFS_H_
#define DEFS_H_

#include "Sensor.h"

// TCP/IP DEFINES
// SC = server -> client
// CS = client -> server
#define TCP_PORT_GUI 6665
#define TCP_MSG_LENGTH 1024
#define TCP_CMD_SENSOR_DATA_SC 0x00
#define TCP_CMD_SENSOR_INTERVAL_SC 0x02
#define TCP_CMD_SENSOR_INTERVAL_CS 0x03


struct tcp_data {
	int newsockfd;
	std::string name;

	tcp_data() {
		newsockfd = 0;
	}

	tcp_data(int newsock)
	{
		newsockfd = newsock;
	}
};

struct sensorData_s {
	Sensor::vectorInt16 accRaw;
	Sensor::vector acc;
	Sensor::vectorInt16 gyroRaw;
	Sensor::vector gyro;
	Sensor::vectorInt16 magRaw;
	Sensor::vector mag;
	int8_t poti;
};


#endif
