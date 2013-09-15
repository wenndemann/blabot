/*
 * SensorHandler.h
 *
 *  Created on: Mar 14, 2013
 *      Author: reinhard
 */

#ifndef SENSORHANDLER_H_
#define SENSORHANDLER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pthread.h>

#include "defs.h"
#include "i2c.h"

#include "LSM303.h"
#include "L3G.h"

class SensorHandler {
public:
	SensorHandler();
	SensorHandler(const char* devName, pthread_mutex_t *mutex);
	virtual ~SensorHandler();

	void setMeasuringInterval(int intervalMs);
	sensorData_s* getSensorData() { return &m_sensorData; }
	int getMeasuringInterval() { return m_intervalMs; }

private:
	I2c m_I2cHandler;
	LSM303 m_LSM303;
	L3G m_L3G;
	pthread_t m_threadTimer;
	sensorData_s m_sensorData;
	pthread_mutex_t *m_mutex;
	int m_intervalMs;

	void* m_callbackTimer(void* arg);
	void m_readDataSensor(boost::asio::deadline_timer* t);
	void m_swapInt16(int16_t &inout);
};

#endif /* SENSORHANDLER_H_ */
