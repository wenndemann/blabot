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


#include "../../../include/defs.h"

#include "tools.h"
#include "timer.h"
// SERVER

#define SEMM_NUM_THREADS 8


pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t g_threads[SEMM_NUM_THREADS];
pthread_t g_thread_timer;

sensorData_s sensorData;
I2c i2c("/dev/i2c-0");

void* tcp_accept_players(void* arg);


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

  printf("timer init\n");
  initTimer();
  printf("timer set\n");
  setTimer(10);
  printf("timer ready\n");
  
  //initHardware();
  

	while(true) {
		
		// TODO accept multiple users
		// waiting for clients
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		tcp_data data(newsockfd);
		mapTcpData[numAcceptions] = data;

		//if (newsockfd < 0) 
		//  error("ERROR on accept");

    if (newsockfd == -1) {
      if (EINTR==errno) {
              continue; /* Restart accept */
      }
      else {
              error("Ouch ouch accept");
              //end_of_the_show=TRUE;
      }
    }


		if (pthread_create(&g_threads[numAcceptions], NULL, tcp_accept_players, 
			(void*) &mapTcpData[numAcceptions]))
        { error("Failed to create user acceptance thread"); }
		
		numAcceptions++;
		if (numAcceptions >= SEMM_NUM_THREADS)
			close(newsockfd);
	}

	close(sockfd);
	while(1);
		
	return 0; 
}


void* tcp_accept_players(void* arg) 
{
	int n;
	uint8_t buf[128];
	tcp_data data = *((tcp_data*) arg);
	
	__MSG("user %d connected\n", data.newsockfd);
	
	while(true) {
		/*n = read(data.newsockfd, &buf, sizeof(buf));
		if (n < 0) 
			error("ERROR reading from socket");
		else {
			switch (buf[0]) {
				case 0: 			//send data*/
					pthread_mutex_lock(&g_mutex);
					n = write(data.newsockfd, (void*) &sensorData , sizeof(sensorData));
					pthread_mutex_unlock(&g_mutex);
					/*if (n < 0) error("ERROR writing to socket");
					break;
				case 1: 			//set enable bits

					break;
				case 2: 			//set i2c read interval, if 0 stop

					break;
				default:		//no command recognized
				  break;
			}

		}*/
	usleep(10000);
	}

	return NULL;
}









