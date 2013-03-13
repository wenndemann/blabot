#include "timer.h"

timer_t g_timer;

//void timerInterrupt(int sig, siginfo_t *si, void *uc) { 
void timerInterrupt() {
  	uint8_t l, h;
  	uint16_t a = 0;
    //sensorData_s *sensorData;
    //sensorData = ((sensorData_s *) si->si_value.sival_ptr);

	
		pthread_mutex_lock(&g_mutex);

    // read accelerometer data from sensor
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_X, &sensorData.accel[0], 
			sizeof(sensorData.accel));


    // read gyroscope data from sensor
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_X, &sensorData.gyro[0], 
		  sizeof(sensorData.gyro));
    for (int i = 0; i < 3; i++) { swapInt16(sensorData.gyro[i]); }
	  

    // read magnetometer data from sensor
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_X, &sensorData.mag[0], 
  	  sizeof(sensorData.mag));
  	for (int i = 0; i < 3; i++) { swapInt16(sensorData.mag[i]); }

    // read potentiometer data from sensor
		i2c.receive(I2C_POTI_ADDR, I2C_POTI_CTRL, &l, 3);
		sensorData.poti = (int8_t) (l - 128);

		
		pthread_mutex_unlock(&g_mutex);
		//printf("poti: %d\n",sensorData.gyro[2]);
		//  sensorData.mag[0],sensorData.mag[1],sensorData.mag[2]);


}

void swapInt16(int16_t &inout) {
  uint8_t hibyte = (inout & 0xff00) >> 8; // extract the high byte
  uint8_t lobyte = (inout & 0xff); // extract the low byte
  inout = lobyte << 8 | hibyte; // combine them in the reverse order    
}

void print(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, int* count)
{
  if (5)
  {
    //std::cout << *count << "\n";
    //++(*count);
    
    timerInterrupt();

    t->expires_at(t->expires_at() + boost::posix_time::microseconds(10000));
    t->async_wait(boost::bind(print,
          boost::asio::placeholders::error, t, count));
  }
}

void* callback_timer(void* arg) 
{
  boost::asio::io_service io;

  int count = 0;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.async_wait(boost::bind(print,
        boost::asio::placeholders::error, &t, &count));

  io.run();

  printf("Final count is %d\n", count);
}


void initTimer() {
    /*struct sigaction action;
    sigfillset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = timerInterrupt;
    sigaction(SIG_NUM, &action, NULL);

    struct sigevent event;
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = SIG_NUM;
    event.sigev_value.sival_ptr = &sensorData;

    timer_create(CLOCK_REALTIME, &event, &g_timer);*/
    
    if (pthread_create(&g_thread_timer, NULL, callback_timer, NULL));
    

    initHardware();
    
}

void setTimer(int ms) {
    /*struct itimerspec timerspec;

    timerspec.it_value.tv_sec = 0;
    timerspec.it_value.tv_nsec = 1;
    timerspec.it_interval.tv_sec = ms / 1000;
    timerspec.it_interval.tv_nsec = (ms % 1000) * 1e6;

    timer_settime(g_timer, 0, &timerspec, NULL);*/
    
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

