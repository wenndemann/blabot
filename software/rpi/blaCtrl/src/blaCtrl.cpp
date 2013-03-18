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
#include "../../../include/defs.h"
#include "tools.h"
#include "Sensor.h"
// SERVER

#define SEMM_NUM_THREADS 8


pthread_mutex_t g_sensorMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_clientMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t g_pthreadTcpIpListen;
Sensor g_sensor("/dev/i2c-0", &g_sensorMutex);
std::map<int, Client> g_clientMap;
void* tcpIpListen(void* arg);

int main(int argc, char** argv)
{
	if(pthread_mutex_init(&g_sensorMutex, NULL))
		perror("Faild to initialize sensor mutex");
	if(pthread_mutex_init(&g_clientMutex, NULL))
		perror("Faild to initialize client mutex");

	printf("timer init\n");
	g_sensor.setMeasuringInterval(10);


	return 0;
}

void* tcpIpListen(void* arg) {
	int sockfd, newsockfd, portno;
	std::map<int, tcp_data> mapTcpData;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	Client *cli;

	// intialize server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	perror("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = TCP_PORT_GUI;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR on binding");

	std::map<int,Client>::iterator it;

	while(true) {
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
		  perror("ERROR on accept");

		cli = new Client();
		cli->setSensor(&g_sensor);
		cli->setFd(newsockfd);
		cli->setSensorMutex(&g_sensorMutex);
		cli->setClientMutex(&g_clientMutex);
		cli->setClientMap(&g_clientMap);
		g_clientMap.insert(std::pair<int, Client>(newsockfd, *cli));
		cli->run();

		printf("\nclient list: \n");
		for(it=g_clientMap.begin(); it != g_clientMap.end(); ++it)
			printf("-> client %d in map\n", it->first);
		printf("end of client list\n\n");

	}
	return NULL;
}





