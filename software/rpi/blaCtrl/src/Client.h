/*
 * Client.h
 *
 *  Created on: Mar 18, 2013
 *      Author: reinhard
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <pthread.h>

#include "Sensor.h"


class Client {
public:
	Client();
	virtual ~Client();

	void setSensor(Sensor *sensor) { m_sensor = sensor; }
	void setFd(int fd) { m_fd = fd; }
	void setSensorMutex(pthread_mutex_t *sensorMutex) {m_sensorMutex = sensorMutex; }
	void setClientMutex(pthread_mutex_t *clientMutex) {m_clientMutex = clientMutex; }
	void setClientMap(std::map<int, Client> *clientMap)
		{ m_clientMap = clientMap; }
	void run();

private:
	Sensor *m_sensor;
	int m_fd;
	pthread_mutex_t *m_sensorMutex;
	pthread_mutex_t *m_clientMutex;
	std::map<int, Client> *m_clientMap;


};

#endif /* CLIENT_H_ */