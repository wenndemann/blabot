#include "LSM303.h"
#include <math.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes
#define MAG_ADDRESS            (0x3C >> 1)
#define ACC_ADDRESS_SA0_A_LOW  (0x30 >> 1)
#define ACC_ADDRESS_SA0_A_HIGH (0x32 >> 1)

// Constructors ////////////////////////////////////////////////////////////////

LSM303::LSM303()
{
  // These are just some values for a particular unit; it is recommended that
  // a calibration be done for your particular unit.
  m_maxMag.x = +540; m_maxMag.y = +500; m_maxMag.z = 180;
  m_minMag.x = -520; m_minMag.y = -570; m_minMag.z = -770;

  _device = LSM303_DEVICE_AUTO;
  acc_address = ACC_ADDRESS_SA0_A_HIGH;

  io_timeout = 0;  // 0 = no timeout
  did_timeout = false;

  last_status = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

bool LSM303::timeoutOccurred()
{
  return did_timeout;
}

void LSM303::setTimeout(unsigned int timeout)
{
  io_timeout = timeout;
}

unsigned int LSM303::getTimeout()
{
  return io_timeout;
}

void LSM303::init(byte device, byte sa0_a)
{
  _device = device;
  switch (_device)
  {
    case LSM303DLH_DEVICE:
    case LSM303DLM_DEVICE:
      if (sa0_a == LSM303_SA0_A_LOW)
        acc_address = ACC_ADDRESS_SA0_A_LOW;
      else if (sa0_a == LSM303_SA0_A_HIGH)
        acc_address = ACC_ADDRESS_SA0_A_HIGH;
      else
        acc_address = (detectSA0_A() == LSM303_SA0_A_HIGH) ? ACC_ADDRESS_SA0_A_HIGH : ACC_ADDRESS_SA0_A_LOW;
  	  break;

    case LSM303DLHC_DEVICE:
      acc_address = ACC_ADDRESS_SA0_A_HIGH;
      break;

    default:
      // try to auto-detect device
      if (detectSA0_A() == LSM303_SA0_A_HIGH)
      {
        // if device responds on 0011001b (SA0_A is high), assume DLHC
        acc_address = ACC_ADDRESS_SA0_A_HIGH;
        _device = LSM303DLHC_DEVICE;
      }
      else
      {
        // otherwise, assume DLH or DLM (pulled low by default on Pololu boards); query magnetometer WHO_AM_I to differentiate these two
        acc_address = ACC_ADDRESS_SA0_A_LOW;
        _device = (readMagReg(LSM303_WHO_AM_I_M) == 0x3C) ? LSM303DLM_DEVICE : LSM303DLH_DEVICE;
      }
      break;
  }
}

// Turns on the LSM303's accelerometer and magnetometers and places them in normal
// mode.
void LSM303::enableDefault(void)
{
  // Enable Accelerometer
  // 0x27 = 0b00100111
  // Normal power mode, all axes enabled
  writeAccReg(LSM303_CTRL_REG1_A, 0x27);

  if (_device == LSM303DLHC_DEVICE)
    writeAccReg(LSM303_CTRL_REG4_A, 0x08); // DLHC: enable high resolution mode

  // Enable Magnetometer
  // 0x00 = 0b00000000
  // Continuous conversion mode
  writeMagReg(LSM303_MR_REG_M, 0x00);
}

// Writes an accelerometer register
void LSM303::writeAccReg(byte reg, byte value)
{
  m_I2cHandler.send(acc_address, reg, &value, sizeof(byte));
}

// Reads an accelerometer register
byte LSM303::readAccReg(byte reg)
{
  byte value;
  m_I2cHandler.receive(acc_address, reg, &value, sizeof(byte));
  return value;
}

// Writes a magnetometer register
void LSM303::writeMagReg(byte reg, byte value)
{
  m_I2cHandler.send(MAG_ADDRESS, reg, &value, sizeof(byte));
}

// Reads a magnetometer register
byte LSM303::readMagReg(int reg)
{
  byte value;

  // if dummy register address (magnetometer Y/Z), use device type to determine actual address
  if (reg < 0)
  {
    switch (reg)
    {
      case LSM303_OUT_Y_H_M:
        reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Y_H_M : LSM303DLM_OUT_Y_H_M;
        break;
      case LSM303_OUT_Y_L_M:
        reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Y_L_M : LSM303DLM_OUT_Y_L_M;
        break;
      case LSM303_OUT_Z_H_M:
        reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Z_H_M : LSM303DLM_OUT_Z_H_M;
        break;
      case LSM303_OUT_Z_L_M:
        reg = (_device == LSM303DLH_DEVICE) ? LSM303DLH_OUT_Z_L_M : LSM303DLM_OUT_Z_L_M;
        break;
    }
  }

  m_I2cHandler.receive(MAG_ADDRESS, reg, &value, sizeof(byte));

  return value;
}

void LSM303::setMagGain(magGain value)
{
  byte val = (byte) value;
  m_I2cHandler.send(MAG_ADDRESS, LSM303_CRB_REG_M, &val, sizeof(byte));
}

// Reads the 3 accelerometer channels and stores them in vector a
void LSM303::readAcc(void)
{
  m_I2cHandler.receive(acc_address, LSM303_OUT_X_L_A | (1 << 7), &m_dataAccRaw, 3*sizeof(int16_t));
  //std::cout << "Read accRaw: (" << m_dataAccRaw.x << "," << m_dataAccRaw.y << "," << m_dataAccRaw.z << ")" << std::endl;
  m_dataAcc.set(m_dataAccRaw.x, m_dataAccRaw.y, m_dataAccRaw.z);
  //std::cout << "Before Normalize Read acc: (" << m_dataAcc.x << "," << m_dataAcc.y << "," << m_dataAcc.z << ")" << std::endl;
  vector_normalize(m_dataAcc);
  //std::cout << "After Normalize Read acc: (" << m_dataAcc.x << "," << m_dataAcc.y << "," << m_dataAcc.z << ")" << std::endl;
}

// Reads the 3 magnetometer channels and stores them in vector m
void LSM303::readMag(void)
{
  m_I2cHandler.receive(MAG_ADDRESS, LSM303_OUT_X_H_M, &m_dataMagRaw, 3*sizeof(int16_t));
  m_dataMag = vector(m_dataMagRaw);
  vector_normalize(m_dataMag);
}

// Reads all 6 channels of the LSM303 and stores them in the object variables
void LSM303::read(void)
{
  readAcc();
  readMag();
}

// Returns the number of degrees from the -Y axis that it
// is pointing.
int LSM303::heading(void)
{
  return heading(vector(0.0f,-1.0f,0.0f));
}

// Returns the angular difference in the horizontal plane between the
// From vector and North, in degrees.
//
// Description of heading algorithm:
// Shift and scale the magnetic reading based on calibration data to
// to find the North vector. Use the acceleration readings to
// determine the Up vector (gravity is measured as an upward
// acceleration). The cross product of North and Up vectors is East.
// The vectors East and North form a basis for the horizontal plane.
// The From vector is projected into the horizontal plane and the
// angle between the projected vector and north is returned.
int LSM303::heading(vector from)
{
    // shift and scale
    m_dataMag.x = (m_dataMag.x - m_minMag.x) / (m_maxMag.x - m_minMag.x) * 2 - 1.0;
    m_dataMag.y = (m_dataMag.y - m_minMag.y) / (m_maxMag.y - m_minMag.y) * 2 - 1.0;
    m_dataMag.z = (m_dataMag.z - m_minMag.z) / (m_maxMag.z - m_minMag.z) * 2 - 1.0;

    vector temp_a(m_dataAcc);
    vector temp_m(m_dataMag);

    // normalize
    vector_normalize(temp_a);
    //vector_normalize(&m);

    // compute E and N
    vector E;
    vector N;
    vector_cross(temp_m, temp_a, E);
    vector_normalize(E);
    vector_cross(temp_a, E, N);

    // compute heading
    int heading = round(atan2(vector_dot(E, from), vector_dot(N, from)) * 180 / M_PI);
    if (heading < 0) heading += 360;
  return heading;
}

// Private Methods //////////////////////////////////////////////////////////////

byte LSM303::detectSA0_A(void)
{
  byte value;
  int iRet = m_I2cHandler.receive(
    ACC_ADDRESS_SA0_A_HIGH, LSM303_CTRL_REG1_A, &value, sizeof(byte));

  if (iRet >= 0)
	return LSM303_SA0_A_HIGH;
  else
	return LSM303_SA0_A_LOW;
}
