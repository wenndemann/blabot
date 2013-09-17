/*
 * Sensor.h
 *
 *  Created on: Sep 15, 2013
 *      Author: michael
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <boost/noncopyable.hpp>
#include "i2c.h"

typedef uint8_t byte;

class Sensor : boost::noncopyable
{
  public:

	struct vectorInt16
	{
	    vectorInt16() {x = y = z = 0;}
	    vectorInt16(int16_t X, int16_t Y, int16_t Z) {x=X;y=Y;z=Z;}
	    void set(int16_t X, int16_t Y, int16_t Z) {x=X;y=Y;z=Z;}
	    int16_t x, y, z;
	};

	struct vector
	{
	    vector() {x = y = z = 0.0f;}
	    vector(float X, float Y, float Z) {x=X;y=Y;z=Z;}
	    vector(const vectorInt16 &v16) {
	        x = static_cast<float>(v16.x);
	        y = static_cast<float>(v16.y);
	        z = static_cast<float>(v16.z);
	    }
	    void set(float X, float Y, float Z) {x=X;y=Y;z=Z;}
	    void set(int16_t X, int16_t Y, int16_t Z) {
	        x = static_cast<float>(X);
	    	y = static_cast<float>(Y);
	    	z = static_cast<float>(Z);
	    }
	    float x, y, z;
	};

	Sensor();
	Sensor(const char* devName);
	virtual ~Sensor();

	void setI2c(const I2c& I2cHandler);
	virtual void enableDefault(void) = 0;

	void writeReg(byte addr, byte reg, byte value);
	byte readReg(byte addr, byte reg);

	virtual void read(void) = 0;

	// vector functions
	static void vector_cross(const vector &a, const vector &b, vector& out);
	static float vector_dot(const vector& a, const vector& b);
	static void vector_normalize(vector& v);

  protected:
	I2c m_I2cHandler;
};

#endif /* SENSOR_H_ */
