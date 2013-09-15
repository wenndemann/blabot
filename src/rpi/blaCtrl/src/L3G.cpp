#include "L3G.h"
#include <math.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes
#define L3G4200D_ADDRESS_SA0_LOW  (0xD0 >> 1)
#define L3G4200D_ADDRESS_SA0_HIGH (0xD2 >> 1)
#define L3GD20_ADDRESS_SA0_LOW    (0xD4 >> 1)
#define L3GD20_ADDRESS_SA0_HIGH   (0xD6 >> 1)

// Constructors ////////////////////////////////////////////////////////////////

L3G::L3G()
{
  L3G("/dev/i2c-1");
}

L3G::L3G(const char* devName) : Sensor(devName)
{
  _device = 0;
  address = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

bool L3G::init(byte device, byte sa0)
{
  _device = device;
  switch (_device)
  {
    case L3G4200D_DEVICE:
      if (sa0 == L3G_SA0_LOW)
      {
        address = L3G4200D_ADDRESS_SA0_LOW;
        return true;
      }
      else if (sa0 == L3G_SA0_HIGH)
      {
        address = L3G4200D_ADDRESS_SA0_HIGH;
        return true;
      }
      else
        return autoDetectAddress();
      break;

    case L3GD20_DEVICE:
      if (sa0 == L3G_SA0_LOW)
      {
        address = L3GD20_ADDRESS_SA0_LOW;
        return true;
      }
      else if (sa0 == L3G_SA0_HIGH)
      {
        address = L3GD20_ADDRESS_SA0_HIGH;
        return true;
      }
      else
        return autoDetectAddress();
      break;

    default:
      return autoDetectAddress();
  }
}

// Turns on the L3G's gyro and places it in normal mode.
void L3G::enableDefault(void)
{
  // 0x0F = 0b00001111
  // Normal power mode, all axes enabled
  writeReg(L3G_CTRL_REG1, 0x0F);
}

// Writes a gyro register
void L3G::writeReg(byte reg, byte value)
{
  m_I2cHandler->send(address, reg, &value, sizeof(byte));
}

// Reads a gyro register
byte L3G::readReg(byte reg)
{
  byte value;
  m_I2cHandler->receive(address, reg, &value, sizeof(byte));

  return value;
}

// Reads the 3 gyro channels and stores them in vector g
void L3G::read()
{
  m_I2cHandler->receive(address, L3G_OUT_X_L | (1 << 7), &m_dataGyroRaw, 3*sizeof(int16_t));
  m_dataGyro = vector(m_dataGyroRaw);
  vector_normalize(m_dataGyro);
}

// Private Methods //////////////////////////////////////////////////////////////

bool L3G::autoDetectAddress(void)
{
  // try each possible address and stop if reading WHO_AM_I returns the expected response
  address = L3G4200D_ADDRESS_SA0_LOW;
  if (readReg(L3G_WHO_AM_I) == 0xD3) return true;
  address = L3G4200D_ADDRESS_SA0_HIGH;
  if (readReg(L3G_WHO_AM_I) == 0xD3) return true;
  address = L3GD20_ADDRESS_SA0_LOW;
  if (readReg(L3G_WHO_AM_I) == 0xD4) return true;
  address = L3GD20_ADDRESS_SA0_HIGH;
  if (readReg(L3G_WHO_AM_I) == 0xD4) return true;

  return false;
}
