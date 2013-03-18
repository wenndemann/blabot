/*
 * Sensor.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: reinhard
 */

#include "Sensor.h"

typedef  void* (Sensor::*Thread2Ptr)(void*);
typedef  void* (*PthreadPtr)(void*);

Sensor::Sensor() {
	Sensor("/dev/i2c0", NULL);
}

Sensor::Sensor(const char* devName, pthread_mutex_t *mutex) {
	m_i2cConnection = new I2c(devName);
	m_mutex = mutex;
	printf("size of sensorData: %d\n", sizeof(m_sensorData));
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::setMeasuringInterval(int intervalMs) {
	Thread2Ptr t = &Sensor::m_callbackTimer;
	PthreadPtr p = *(PthreadPtr*)&t;

	m_intervalMs = intervalMs;
	if (intervalMs) {
		m_initHardware();
	    pthread_create(&m_threadTimer, NULL, p, this);
	}
}

void* Sensor::m_callbackTimer(void* arg)
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(m_intervalMs));
	t.async_wait(boost::bind(&Sensor::m_readDataSensor, this, &t));
	io.run();
	return NULL;
}

void Sensor::m_readDataSensor(boost::asio::deadline_timer* t) {
	uint8_t temp;

	if(m_intervalMs) {
		pthread_mutex_lock(m_mutex);
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
		pthread_mutex_unlock(m_mutex);
		t->expires_at(t->expires_at() + boost::posix_time::milliseconds(m_intervalMs));
		t->async_wait(boost::bind(&Sensor::m_readDataSensor, this, t));
		//printf("gyro: %d\n",m_sensorData.gyro[0]); //TODO remove this line after commissioning
	}
}

void Sensor::m_initHardware() {
	uint8_t temp;

	temp = 0x08;
	m_i2cConnection->send(I2C_ACCEL_ADDR, I2C_ACCEL_POWER_CTL, &temp, sizeof(temp));
	m_i2cConnection->send(I2C_ACCEL_ADDR, I2C_ACCEL_DATA_FORMAT, &temp, sizeof(temp));

	temp = 0x80;
	m_i2cConnection->send(I2C_GYRO_ADDR, I2C_GYRO_POWER_CTL, &temp, sizeof(temp));
	temp = 0x09;
	m_i2cConnection->send(I2C_GYRO_ADDR, I2C_GYRO_DLPF_FS, &temp, sizeof(temp));
	temp = 0x02;
	m_i2cConnection->send(I2C_GYRO_ADDR, I2C_GYRO_POWER_CTL, &temp, sizeof(temp));

	temp = 0x00;
	m_i2cConnection->send(I2C_MAG_ADDR, I2C_MAG_MODE, &temp, sizeof(temp));
}

void Sensor::m_swapInt16(int16_t &inout) {
	uint8_t hibyte = (inout & 0xff00) >> 8; // extract the high byte
	uint8_t lobyte = (inout & 0xff); // extract the low byte
	inout = lobyte << 8 | hibyte; // combine them in the reverse order
}
