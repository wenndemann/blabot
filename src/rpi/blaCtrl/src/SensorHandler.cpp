/*
 * Sensor.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: reinhard
 */

#include "SensorHandler.h"

typedef  void* (SensorHandler::*Thread2Ptr)(void*);
typedef  void* (*PthreadPtr)(void*);

SensorHandler::SensorHandler() {
	SensorHandler("/dev/i2c0", NULL);
}

SensorHandler::SensorHandler(const char* devName, pthread_mutex_t *mutex) {
	m_I2cHandler.openDev(devName);

	m_LSM303.setI2c(m_I2cHandler);
	m_LSM303.init(LSM303DLHC_DEVICE, LSM303_SA0_A_HIGH);
	m_LSM303.enableDefault();

	m_L3G.setI2c(m_I2cHandler);;
	m_L3G.init(L3GD20_DEVICE, L3G_SA0_HIGH);
	m_L3G.enableDefault();

	m_mutex = mutex;
	m_intervalMs = 1000;
	//printf("size of sensorData: %d\n", sizeof(m_sensorData));
}

SensorHandler::~SensorHandler(){}

void SensorHandler::setMeasuringInterval(int intervalMs) {
	Thread2Ptr t = &SensorHandler::m_callbackTimer;
	PthreadPtr p = *(PthreadPtr*)&t;

	m_intervalMs = intervalMs;
	if (intervalMs) {
	    pthread_create(&m_threadTimer, NULL, p, this);
	}
}

void* SensorHandler::m_callbackTimer(void* arg)
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(m_intervalMs));
	t.async_wait(boost::bind(&SensorHandler::m_readDataSensor, this, &t));
	io.run();
	return NULL;
}

void SensorHandler::m_readDataSensor(boost::asio::deadline_timer* t) {

	if(m_intervalMs) {
		pthread_mutex_lock(m_mutex);
		{
			// Accelerometer
			m_LSM303.readAcc();
			m_LSM303.getAcc(m_sensorData.acc);
			m_LSM303.getAccRaw(m_sensorData.accRaw);

			// Magnetometer
			m_LSM303.readMag();
		    m_LSM303.getMag(m_sensorData.mag);
		    m_LSM303.getMagRaw(m_sensorData.magRaw);

		    std::cout << "accX:\t" << m_sensorData.accRaw.x << std::endl << "accY:\t" << m_sensorData.accRaw.y
                      << std::endl << "accZ:\t" << m_sensorData.accRaw.z << std::endl << std::endl;


		    // Magnetometer
			m_L3G.read();
			m_L3G.getGyro(m_sensorData.gyro);
			m_L3G.getGyroRaw(m_sensorData.gyroRaw);

			//std::cout << "gyroX:\t" << m_sensorData.gyro.x << std::endl << "gyroY:\t" << m_sensorData.gyro.y
			//                      << std::endl << "gyroZ:\t" << m_sensorData.gyro.z << std::endl << std::endl;


		    //sleep(1); // TODO replace
		}
		pthread_mutex_unlock(m_mutex);
		t->expires_at(t->expires_at() + boost::posix_time::milliseconds(m_intervalMs));
		t->async_wait(boost::bind(&SensorHandler::m_readDataSensor, this, t));
		//printf("gyro: %d\n",m_sensorData.gyro[0]); //TODO remove this line after commissioning
	}
}

void SensorHandler::m_swapInt16(int16_t &inout) {
	uint8_t hibyte = (inout & 0xff00) >> 8; // extract the high byte
	uint8_t lobyte = (inout & 0xff); // extract the low byte
	inout = lobyte << 8 | hibyte; // combine them in the reverse order
}
