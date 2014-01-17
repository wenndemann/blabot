#include "i2c.h"

boost::mutex I2c::m_mutex_0;
boost::mutex I2c::m_mutex_1;

I2c::I2c()
{
	m_fd = 0;
	m_bDev_0 = true;
}

I2c::I2c(const I2c& other)
{
	this->m_fd = other.m_fd;
	this->m_bDev_0 = other.m_bDev_0;
}

I2c& I2c::operator = (const I2c& other)
{
	this->m_fd = other.m_fd;
	this->m_bDev_0 = other.m_bDev_0;
	return *this;
}

I2c::~I2c() {}

bool I2c::openDev(const char* devName)
{
    if(strcmp(devName,"/dev/i2c-0") == 0)
  		m_bDev_0 = false;

	m_bDev_0? m_mutex_0.lock() : m_mutex_1.lock();
	if((m_fd = open(devName, O_RDWR)) < 0) {
		__WNG("I2C open error! %d\n", m_fd);
		m_bDev_0? m_mutex_0.unlock() : m_mutex_1.unlock();
		return false;
	}
	std::cout << "m_fd = " << m_fd <<  " devname " << devName << std::endl;
	m_bDev_0? m_mutex_0.unlock() : m_mutex_1.unlock();
	return true;
}

int I2c::send(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length + 1];
  int iRet = 0;

  m_bDev_0? m_mutex_0.lock() : m_mutex_1.lock();
  if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0) { __WNG("I2C set adress error!\n"); }
  buf[0] = i2cCmd;
  memcpy(&buf[1], (uint8_t*) data, length);
  iRet = write(m_fd, buf, length + 1);
  if(iRet != length + 1) { __WNG("I2C write error!\n"); }
  m_bDev_0? m_mutex_0.unlock() : m_mutex_1.unlock();

  //std::cout << "I2c::write(" << (int)i2cAddr << ", " << (int)i2cCmd << ", data, " << (int)length << ") returns " << iRet << std::endl;

  return iRet;
}

int I2c::receive(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length) {
  uint8_t buf[length];
  int iRet = 0;

  m_bDev_0? m_mutex_0.lock() : m_mutex_1.lock();
  if(ioctl(m_fd, I2C_SLAVE, i2cAddr) < 0) { __WNG("I2C set adress error!\n"); }
  buf[0] = i2cCmd;
  if(write(m_fd, buf, 1) != 1) { __WNG("I2C write error!\n"); perror(""); }
  iRet = read(m_fd, buf, length);
  if(iRet != length) { __WNG("I2C read error!\n"); perror(""); }
  m_bDev_0? m_mutex_0.unlock() : m_mutex_1.unlock();

  //std::cout << "I2c::receive(" << (int)i2cAddr << ", " << (int)i2cCmd << ", data, " << (int)length << ") returns " << iRet << std::endl;

  memcpy((uint8_t*) data, &buf[0], length);
  return iRet;
}
