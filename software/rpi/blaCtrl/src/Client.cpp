/*
 * Client.cpp
 *
 *  Created on: Mar 18, 2013
 *      Author: reinhard
 */

#include "Client.h"

typedef  void* (Client::*Thread2Ptr)(void*);
typedef  void* (*PthreadPtr)(void*);

Client::Client() {
	// TODO Auto-generated constructor stub

}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

void Client::run() {
	Thread2Ptr t = &Client::m_sendSensorData;
	PthreadPtr p = *(PthreadPtr*)&t;
	if (pthread_create(&m_pthreadSendSensorData, 0, p, this) < 0) {
		pthread_detach(m_pthreadSendSensorData);
		perror("ERROR create send sensor data thread: ");
	}
	Thread2Ptr t2 = &Client::m_parseTcpIp;
	PthreadPtr p2 = *(PthreadPtr*)&t2;
	if (pthread_create(&m_pthreadParseTcpIp, 0, p2, this) < 0) {
		pthread_detach(m_pthreadParseTcpIp);
		perror("ERROR create tcp parse thread: ");
	}

}

void* Client::m_sendSensorData(void* arg) {
	int n = 0;
	uint8_t buf[21];
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::
		milliseconds(m_sensor->getMeasuringInterval()));

	buf[0] = TCP_CMD_SENSOR_DATA_SC;
	printf("start sending sensor data to %d\n", m_fd);
	do {
		t.wait();
		t.expires_at(t.expires_at() + boost::posix_time::
			milliseconds(m_sensor->getMeasuringInterval()));
		pthread_mutex_lock(m_sensorMutex);
			memcpy(&buf[1],m_sensor->getSensorData(),20);
		pthread_mutex_unlock(m_sensorMutex);
		n = write(m_fd, &buf, 21);
		if (n < 0) {
			if (errno == EBADF) break;
			else {
				printf("errorno: %d\n",errno);
				perror("ERROR writing to TCP IP");
				break;
			}
		}
	} while(n);
	printf("stop sending sensor data to %d\n", m_fd);
	m_clientMap->erase(m_fd);
	close(m_fd);
	return NULL;
}

void* Client::m_parseTcpIp(void* arg) {
	int n = 0;
	uint8_t buf[TCP_MSG_LENGTH];
	int16_t tempInt;
	printf("start reading data from %d\n", m_fd);
	do {
		n = read(m_fd, &buf, TCP_MSG_LENGTH);
		if (n < 0) {
			printf("errorno: %d\n",errno);
			perror("ERROR reading to TCP IP");
		}
		switch(buf[0]) {
		case TCP_CMD_SENSOR_INTERVAL_SC:
			tempInt = m_sensor->getMeasuringInterval();
			buf[0] = TCP_CMD_SENSOR_INTERVAL_SC;
			memcpy(&buf[1], &tempInt, sizeof(tempInt));
			buf[4] = '\0';
			write(m_fd, &buf, 4);
			break;
		case TCP_CMD_SENSOR_INTERVAL_CS:
			memcpy(&tempInt, &buf[1], sizeof(tempInt));
			m_sensor->setMeasuringInterval(tempInt);
			printf("%d change sensor interval to %dms\n",
				m_fd, m_sensor->getMeasuringInterval());
			break;
		}
	} while(n);
	printf("stop reading data from %d\n", m_fd);
	m_clientMap->erase(m_fd);
	close(m_fd);
	return NULL;
}
