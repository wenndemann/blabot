#ifndef I2C_H_
#define I2C_H_


#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string>
#include <boost/thread/mutex.hpp>

#include "tools.h"

class I2c {
  public:
    I2c();
    I2c(const I2c& other);
    I2c& operator = (const I2c& other);
    ~I2c();
    
    bool openDev(const char* devName);
    int receive(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length);
    int send(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length);
  
  private:
    void setCmd(uint8_t I2cCmd, int i2cAddr, int fd);
    
    int m_fd;
    boost::mutex m_mutex;
};


#endif
