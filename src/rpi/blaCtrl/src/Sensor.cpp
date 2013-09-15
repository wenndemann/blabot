/*
 * Sensor.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: michael
 */

#include "Sensor.h"

Sensor::Sensor() {
}

Sensor::Sensor(const char* devName) {
	m_I2cHandler = new I2c(devName);
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::writeReg(byte addr, byte reg, byte value)
{
	m_I2cHandler->send(addr, reg, &value, sizeof(byte));
}

byte Sensor::readReg(byte addr, byte reg)
{
	byte value;
    m_I2cHandler->receive(addr, reg, &value, sizeof(byte));
    return value;
}

void Sensor::vector_cross(const vector &a, const vector &b, vector& out)
{
  out.x = a.y*b.z - a.z*b.y;
  out.y = a.z*b.x - a.x*b.z;
  out.z = a.x*b.y - a.y*b.x;
}

float Sensor::vector_dot(const vector& a,const vector& b)
{
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

void Sensor::vector_normalize(vector &v)
{
  float mag = sqrt(vector_dot(v,v));
  v.x /= mag;
  v.y /= mag;
  v.z /= mag;
}
