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
	m_LSM303 = new LSM303(devName);
	m_LSM303->init(LSM303DLHC_DEVICE, LSM303_SA0_A_HIGH);
	m_LSM303->enableDefault();

	m_L3G = new L3G(devName);
	m_L3G->init();
	m_L3G->enableDefault();

	m_mutex = mutex;
	m_intervalMs = 1000;
	printf("size of sensorData: %d\n", sizeof(m_sensorData));
}

SensorHandler::~SensorHandler() {
	// TODO Auto-generated destructor stub
}

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
	uint8_t temp;

	if(m_intervalMs) {
		pthread_mutex_lock(m_mutex);
		    /*
			// read accelerometer data from sensor
			m_i2cConnection->receive(I2C_ACCEL_ADDR, I2C_ACCEL_X, &m_sensorData.accel[0], sizeof(m_sensorData.accel));
			// read gyroscope data from sensor
			m_i2cConnection->receive(I2C_GYRO_ADDR, I2C_GYRO_X, &m_sensorData.gyro[0], sizeof(m_sensorData.gyro));
			for (int i = 0; i < 3; i++) { m_swapInt16(m_sensorData.gyro[i]); }
			// read magnetometer data from sensor
			m_i2cConnection->receive(I2C_MAG_ADDR, I2C_MAG_X, &m_sensorData.mag[0], sizeof(m_sensorData.mag));
			for (int i = 0; i < 3; i++) { m_swapInt16(m_sensorData.mag[i]); }
			// read potentiometer data from sensor
			m_i2cConnection ->receive(I2C_POTI_ADDR, I2C_POTI_CTRL, &temp, 3);
			m_sensorData.poti = (int8_t) (temp - 128);
			*/
		{
			// Accelerometer
			m_LSM303->readAcc();
			m_LSM303->getAccRaw(m_sensorData.accel);

			// Magnetometer
			m_LSM303->readMag();
		    m_LSM303->getMagRaw(m_sensorData.mag);


		    std::cout << "accX:\t" << m_sensorData.accel.x << std::endl << "accY:\t" << m_sensorData.accel.y
                      << std::endl << "accZ:\t" << m_sensorData.accel.z << std::endl << std::endl;


		    // Magnetometer
			m_L3G->read();
			m_L3G->getGyroRaw(m_sensorData.gyro);

			std::cout << "gyroX:\t" << m_sensorData.gyro.x << std::endl << "gyroY:\t" << m_sensorData.gyro.y
			                      << std::endl << "gyroZ:\t" << m_sensorData.gyro.z << std::endl << std::endl;


		    sleep(1);
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
