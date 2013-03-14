#ifndef TIMER_H_
#define TIMER_H_

#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sys/types.h> 
#include <netinet/in.h>

#include "i2c.h"
#include "defs.h"

#define SIG_NUM 	SIGUSR1

extern sensorData_s sensorData;
extern pthread_mutex_t g_mutex;
extern I2c i2c;
extern pthread_t g_thread_timer;




void initTimer();
void setTimer(int ms);
void initHardware();

void swapInt16(int16_t &inout);

#endif
