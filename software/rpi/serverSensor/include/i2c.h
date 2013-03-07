#ifndef I2C_H_
#define I2C_H_


#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string>

#include "tools.h"

class I2c {
  public:
    I2c();
    I2c(const char* devName);
    
    void receive(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length);
    void send(uint8_t i2cAddr, uint8_t i2cCmd, void* data, uint8_t length);
  
  private:
    void setCmd(uint8_t I2cCmd, int i2cAddr, int fd);
    
    int m_fd;
};


#endif
