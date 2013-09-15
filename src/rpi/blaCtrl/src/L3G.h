#ifndef L3G_h
#define L3G_h

// includes

#include "Sensor.h"

// device types

#define L3G_DEVICE_AUTO 0
#define L3G4200D_DEVICE 1
#define L3GD20_DEVICE   2


// SA0 states

#define L3G_SA0_LOW  0
#define L3G_SA0_HIGH 1
#define L3G_SA0_AUTO 2

// register addresses

#define L3G_WHO_AM_I      0x0F

#define L3G_CTRL_REG1     0x20
#define L3G_CTRL_REG2     0x21
#define L3G_CTRL_REG3     0x22
#define L3G_CTRL_REG4     0x23
#define L3G_CTRL_REG5     0x24
#define L3G_REFERENCE     0x25
#define L3G_OUT_TEMP      0x26
#define L3G_STATUS_REG    0x27

#define L3G_OUT_X_L       0x28
#define L3G_OUT_X_H       0x29
#define L3G_OUT_Y_L       0x2A
#define L3G_OUT_Y_H       0x2B
#define L3G_OUT_Z_L       0x2C
#define L3G_OUT_Z_H       0x2D

#define L3G_FIFO_CTRL_REG 0x2E
#define L3G_FIFO_SRC_REG  0x2F

#define L3G_INT1_CFG      0x30
#define L3G_INT1_SRC      0x31
#define L3G_INT1_THS_XH   0x32
#define L3G_INT1_THS_XL   0x33
#define L3G_INT1_THS_YH   0x34
#define L3G_INT1_THS_YL   0x35
#define L3G_INT1_THS_ZH   0x36
#define L3G_INT1_THS_ZL   0x37
#define L3G_INT1_DURATION 0x38

class L3G : public Sensor
{
  public:

	struct data {
		data() {x = y = z = 0;}
		int16_t x, y, z;
	};

	struct vector
	{
	  float x, y, z;
	};

	L3G();
    L3G(const char* devName);


    bool init(byte device = L3G_DEVICE_AUTO, byte sa0 = L3G_SA0_AUTO);

    void enableDefault(void);

    void writeReg(byte reg, byte value);
    byte readReg(byte reg);

    void read(void);

    // vector functions
    static void vector_cross(const vector *a, const vector *b, vector *out);
    static float vector_dot(const vector *a,const vector *b);
    static void vector_normalize(vector *a);

    // get methods
    void getGyro(data& dataGyro) { memcpy(&dataGyro,&m_dataGyro,sizeof(m_dataGyro)); }
	int16_t getGyroX(void) { return m_dataGyro.x; }
	int16_t getGyroY(void) { return m_dataGyro.y; }
	int16_t getGyroZ(void) { return m_dataGyro.z; }

  private:
      byte _device; // chip type (4200D or D20)
      byte address;

      bool autoDetectAddress(void);

      data m_dataGyro;
      vector m_vecGyro;
};

#endif



