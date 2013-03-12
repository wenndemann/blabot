#include "timer.h"

timer_t g_timer;

void timerInterrupt(int sig, siginfo_t *si, void *uc) { 
  	uint8_t l, h;
  	uint16_t a = 0;
    sensorData_s *sensorData;
    sensorData = ((sensorData_s *) si->si_value.sival_ptr);

	
		pthread_mutex_lock(&g_mutex);
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_X, &sensorData->accel[0], 
			sizeof(sensorData->accel[0]));
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_Y, &sensorData->accel[1], 
			sizeof(sensorData->accel[1]));
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_Z, &sensorData->accel[2], 
			sizeof(sensorData->accel[2]));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_X, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_X + 1, &l, sizeof(l));
		sensorData->gyro[0] = (((short) (l | (h << 8))));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Y, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Y + 1, &l, sizeof(l));
		sensorData->gyro[1] = (((short) (l | (h << 8))));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Z, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Z + 1, &l, sizeof(l));
		sensorData->gyro[2] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_X, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_X + 1, &l, sizeof(l));
		sensorData->mag[0] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_Y, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_Y + 1, &l, sizeof(l));
		sensorData->mag[1] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_Z, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_Z + 1, &l, sizeof(l));
		sensorData->mag[2] = (((short) (l | (h << 8))));

		i2c.receive(I2C_POTI_ADDR, I2C_POTI_CTRL, &l, 3);
		sensorData->poti = (int8_t) (l - 128);

		
		pthread_mutex_unlock(&g_mutex);
		printf("poti: %d\n",l);
		//  sensorData.mag[0],sensorData.mag[1],sensorData.mag[2]);


}

void initTimer() {
    struct sigaction action;
    sigfillset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = timerInterrupt;
    sigaction(SIG_NUM, &action, NULL);

    struct sigevent event;
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = SIG_NUM;
    event.sigev_value.sival_ptr = &sensorData;

    timer_create(CLOCK_REALTIME, &event, &g_timer);
    initHardware();
}

void setTimer(int ms) {
    struct itimerspec timerspec;

    timerspec.it_value.tv_sec = 0;
    timerspec.it_value.tv_nsec = 1;
    timerspec.it_interval.tv_sec = ms / 1000;
    timerspec.it_interval.tv_nsec = (ms % 1000) * 1e6;

    timer_settime(g_timer, 0, &timerspec, NULL);
}

void initHardware() {
  uint8_t temp;

	__MSG("initialize hardware\n");
	temp = 0x08;
	i2c.send(I2C_ACCEL_ADDR, I2C_ACCEL_POWER_CTL, &temp, sizeof(temp));
	i2c.send(I2C_ACCEL_ADDR, I2C_ACCEL_DATA_FORMAT, &temp, sizeof(temp));

  temp = 0x80;
	i2c.send(I2C_GYRO_ADDR, I2C_GYRO_POWER_CTL, &temp, sizeof(temp));
  temp = 0x09;
	i2c.send(I2C_GYRO_ADDR, I2C_GYRO_DLPF_FS, &temp, sizeof(temp));
  temp = 0x02;
	i2c.send(I2C_GYRO_ADDR, I2C_GYRO_POWER_CTL, &temp, sizeof(temp));
	
	temp = 0x00;
	i2c.send(I2C_MAG_ADDR, I2C_MAG_MODE, &temp, sizeof(temp));
}

