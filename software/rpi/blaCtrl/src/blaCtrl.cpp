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

//#include <signal.h>
//#include <time.h>

#include "Client.h"
#include "defs.h"
#include "tools.h"
#include "Sensor.h"
// SERVER

#define SEMM_NUM_THREADS 8


pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t g_threads[SEMM_NUM_THREADS];
pthread_t g_thread_timer;
Sensor g_sensor("/dev/i2c-0", &g_mutex);

int main(int argc, char** argv)
{
	if(pthread_mutex_init(&g_mutex, NULL))
		perror("Faild to initialize mutex");

	Client *cli;

	printf("timer init\n");
	g_sensor.setMeasuringInterval(10);

	int sockfd, newsockfd, portno;
	std::map<int, tcp_data> mapTcpData;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int numAcceptions = 0;

	// intialize server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	perror("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = SEMM_TCPIP_PORT;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR on binding");


	while(true) {
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
		  perror("ERROR on accept");

    	cli = new Client(g_sensor.getSensorData(), newsockfd, &g_mutex);
	}

	return 0;
}







