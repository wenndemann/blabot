#ifndef TIMER_H_
#define TIMER_H_

#include <signal.h>
#include <time.h>
#include <stdio.h>


#include <sys/types.h> 
#include <netinet/in.h>

#include "i2c.h"
#include "../../../include/defs.h"

#define SIG_NUM 	SIGUSR1

extern sensorData_s sensorData;
extern pthread_mutex_t g_mutex;
extern I2c i2c;


void initTimer();
void setTimer(int ms);
void initHardware();


#endif
