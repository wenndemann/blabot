#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <strings.h>
#include <string>
#include <map>
#include <algorithm>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <math.h>


#include "../../../include/defs.h"
#include "i2c.h"
#include "tools.h"
// SERVER

#define SEMM_NUM_THREADS 8


pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t g_threads[SEMM_NUM_THREADS];
pthread_t i2cThread;
sensorData_s sensorData;


void* tcp_accept_players(void* arg);
void* i2c_sensor_read(void* arg);


void error(const char *msg)
{
	// TODO
	// __line__
	// __file__
    perror(msg);
    exit(1);
}


int main(int argc, char** argv)
{
	if (system("clear") != 0) //Bildschrirm löschen
		error("clear failed!");

	int sockfd, newsockfd, portno;
	std::map<int, tcp_data> mapTcpData;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int numAcceptions = 0;

	// intialize server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = SEMM_TCPIP_PORT;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	
	if(pthread_mutex_init(&g_mutex, NULL))
		error("Faild to initialize mutex");
	if (pthread_create(&i2cThread, NULL, i2c_sensor_read, NULL))
		error("Faild to create i2c thread!");

	while(true) {
		
		// TODO accept multiple users
		// waiting for clients
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		tcp_data data(newsockfd);
		mapTcpData[numAcceptions] = data;

		if (newsockfd < 0) 
		  error("ERROR on accept");
		
		if (pthread_create(&g_threads[numAcceptions], NULL, tcp_accept_players, 
			(void*) &mapTcpData[numAcceptions]))
        { error("Failed to create user acceptance thread"); }
		
		numAcceptions++;
		if (numAcceptions >= SEMM_NUM_THREADS)
			close(newsockfd);
	}

	close(sockfd);
		
	return 0; 
}


void* i2c_sensor_read(void* arg) {
	uint8_t temp;
	uint8_t l, h;
	int16_t bla;
	I2c i2c("/dev/i2c-0");


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

	__MSG("start reading sensor data\n");
	
	while(1) {
		pthread_mutex_lock(&g_mutex);
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_X, &sensorData.accel[0], 
			sizeof(sensorData.accel[0]));
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_Y, &sensorData.accel[1], 
			sizeof(sensorData.accel[1]));
		i2c.receive(I2C_ACCEL_ADDR, I2C_ACCEL_Z, &sensorData.accel[2], 
			sizeof(sensorData.accel[2]));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_X, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_X + 1, &l, sizeof(l));
		sensorData.gyro[0] = (((short) (l | (h << 8))));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Y, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Y + 1, &l, sizeof(l));
		sensorData.gyro[1] = (((short) (l | (h << 8))));
		
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Z, &h, sizeof(h));
		i2c.receive(I2C_GYRO_ADDR, I2C_GYRO_Z + 1, &l, sizeof(l));
		sensorData.gyro[2] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_X, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_X + 1, &l, sizeof(l));
		sensorData.mag[0] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_Y, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_Y + 1, &l, sizeof(l));
		sensorData.mag[1] = (((short) (l | (h << 8))));
	
  	i2c.receive(I2C_MAG_ADDR, I2C_MAG_Z, &h, sizeof(h));
		i2c.receive(I2C_MAG_ADDR, I2C_MAG_Z + 1, &l, sizeof(l));
		sensorData.mag[2] = (((short) (l | (h << 8))));

		i2c.receive(I2C_POTI_ADDR, I2C_POTI_CTRL, &l, 2);
		sensorData.poti = (int8_t) (l - 128);

		
		pthread_mutex_unlock(&g_mutex);
		//printf("poti: %d\n",sensorData.poti);
		//  sensorData.mag[0],sensorData.mag[1],sensorData.mag[2]);
		usleep(1000);
	}
	return NULL;
}


struct werte_s {
	int16_t a,b,c;
}werte;


void* tcp_accept_players(void* arg) 
{
	int n;
	uint8_t buf[128];
	tcp_data data = *((tcp_data*) arg);
	
	__MSG("user %d connected\n", data.newsockfd);
	
	while(true) {
		n = read(data.newsockfd, &buf, sizeof(buf));
		if (n < 0) 
			error("ERROR reading from socket");
		else {
			switch (buf[0]) {
				case: 0			//send data
					pthread_mutex_lock(&g_mutex);
					n = write(data.newsockfd, (void*) &sensorData , sizeof(sensorData));
					pthread_mutex_unlock(&g_mutex);
					if (n < 0) error("ERROR writing to socket");
					break;
				case: 1			//set enable bits
					pthread_mutex_lock(&g_mutex);
					memcpy(&sensorData.enable, &buf[1], 2);
					pthread_mutex_unlock(&g_mutex);
					break;
				case: 2			//set i2c read interval, if 0 stop

					break;
				default:		//no command recognized
			}

		}

		//usleep(10000);
	}

	return NULL;
}









