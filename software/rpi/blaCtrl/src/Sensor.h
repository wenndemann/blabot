/*
 * Sensor.h
 *
 *  Created on: Mar 14, 2013
 *      Author: reinhard
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pthread.h>


#include "i2c.h"
#include "../../../include/defs.h"



class Sensor {



public:
	Sensor();
	Sensor(const char* devName, pthread_mutex_t *mutex);
	virtual ~Sensor();

	void setMeasuringInterval(int intervalMs);
	sensorData_s* getSensorData() {return &m_sensorData;}
	int getMeasuringInterval() { return m_intervalMs; }

private:
	I2c *m_i2cConnection;
	pthread_t m_threadTimer;
	sensorData_s m_sensorData;
	pthread_mutex_t *m_mutex;
	int m_intervalMs;

	void* m_callbackTimer(void* arg);
	void m_readDataSensor(boost::asio::deadline_timer* t);
	void m_swapInt16(int16_t &inout);
	void m_initHardware();
};

#endif /* SENSOR_H_ */
