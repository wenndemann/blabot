#include "i2c.h"

I2c::I2c() {
  I2c("/dev/i2c-1");
}

I2c::I2c(const char* devName) {
	if((m_fd = open(devName, O_RDWR)) < 0) {
		__DIE("I2C open error! %d\n", m_fd);
	}
}

void I2c::send(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length + 1];

	if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0)
    __DIE("I2C set adress error!\n");
  buf[0] = i2cCmd;
  memcpy(&buf[1], (uint8_t*) data, length);
  if(write(m_fd, buf, length + 1) != length + 1)
	  __DIE("I2C write error!\n");
}

void I2c::receive(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length];

 	if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0)
  __DIE("I2C set adress error!\n");
  buf[0] = i2cCmd;
  if(write(m_fd, buf, 1) != 1)
	  __DIE("I2C write error!\n");
	if(read(m_fd, buf, length) != length)
	  __DIE("I2C read error!\n");
  memcpy((uint8_t*) data, &buf[0], length);
}
