#include "i2c.h"

I2c::I2c()
{
	m_fd = 0;
}

I2c::I2c(const I2c& other)
{
	this->m_fd = other.m_fd;
}

I2c& I2c::operator = (const I2c& other)
{
	this->m_fd = other.m_fd;
	return *this;
}

I2c::~I2c() {}

bool I2c::openDev(const char* devName)
{
	m_mutex.lock();
	if((m_fd = open(devName, O_RDWR)) < 0) {
		__WNG("I2C open error! %d\n", m_fd);
		m_mutex.unlock();
		return false;
	}
	//std::cout << "m_fd = " << m_fd <<  " devname " << devName << std::endl;
	m_mutex.unlock();
	return true;
}

int I2c::send(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length + 1];
  int iRet = 0;

  m_mutex.lock();
  if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0) { __WNG("I2C set adress error!\n"); }
  buf[0] = i2cCmd;
  memcpy(&buf[1], (uint8_t*) data, length);
  iRet = write(m_fd, buf, length + 1);
  if(iRet != length + 1) { __WNG("I2C write error!\n"); }
  m_mutex.unlock();

  //std::cout << "I2c::write(" << (int)i2cAddr << ", " << (int)i2cCmd << ", data, " << (int)length << ") returns " << iRet << std::endl;

  return iRet;
}

int I2c::receive(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length];
  int iRet = 0;

  m_mutex.lock();
  if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0) { __WNG("I2C set adress error!\n"); }
  buf[0] = i2cCmd;
  if(write(m_fd, buf, 1) != 1) { __WNG("I2C write error!\n"); perror(""); }
  iRet = read(m_fd, buf, length);
  if(iRet != length) { __WNG("I2C read error!\n"); perror(""); }
  m_mutex.unlock();

  //std::cout << "I2c::receive(" << (int)i2cAddr << ", " << (int)i2cCmd << ", data, " << (int)length << ") returns " << iRet << std::endl;

  memcpy((uint8_t*) data, &buf[0], length);
  return iRet;
}
