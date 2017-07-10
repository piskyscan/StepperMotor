/*
 * basicmove.c
 *
 *  Created on: 30 May 2017
 *      Author:

Complie and linke with gcc -Wall -pthread -o basicmove basicmove.c -lpigpio -lrt -lm

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pigpio.h"


void cleanup()
{
	gpioTerminate();
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


int main(int argc, char *argv[])
{
	// port numbers to use
	int outport1 = 17;
	int outport2 = 27;
	int outport3 = 22;
	int outport4 = 18;

	int outport5 = 5;
	int outport6 = 6;
	int outport7 = 13;
	int outport8 = 26;
	int i = 0;

	int seq[][4] = {
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,1,1},
			{0,0,0,1},
			{1,0,0,1}};

	//	unsigned outport = 17;
	if (argc != 3 && argc != 4)
	{
		printf("Usage: basicMove xxx yyy [steps per second]\n");
		exit(1);
	}


	int ret = gpioInitialise();

	if (ret  < 0)
	{
		fprintf(stderr, "pigpio initialisation failed with %d\n",ret);
		exit(1);
	}



	atexit(&cleanup);


	int x = atoi(argv[1]);
	int y = atoi(argv[2]);

	int sps = 200;

	if (argc == 4)
	{
		sps = atoi(argv[3]);

		if (sps <= 0)
		{
			fprintf(stderr, "Steps per second must be greater than 0\n");
			exit(1);
		}

	}


	double dist = sqrt(x*x + y*y);

	gpioSetMode(outport1, PI_OUTPUT);
	gpioSetMode(outport2, PI_OUTPUT);
	gpioSetMode(outport3, PI_OUTPUT);
	gpioSetMode(outport4, PI_OUTPUT);
	gpioSetMode(outport5, PI_OUTPUT);
	gpioSetMode(outport6, PI_OUTPUT);
	gpioSetMode(outport7, PI_OUTPUT);
	gpioSetMode(outport8, PI_OUTPUT);

	double timeStep = 1.0/sps;




	for (i = 0;i < dist;i++)
	{
		int xoffset = mod((int)(x*i/dist) , 8);
		int yoffset = mod((int)(y*i/dist) , 8);

		gpioWrite(outport1,seq[yoffset][0]);
		gpioWrite(outport2,seq[yoffset][1]);
		gpioWrite(outport3,seq[yoffset][2]);
		gpioWrite(outport4,seq[yoffset][3]);

		gpioWrite(outport5,seq[xoffset][0]);
		gpioWrite(outport6,seq[xoffset][1]);
		gpioWrite(outport7,seq[xoffset][2]);
		gpioWrite(outport8,seq[xoffset][3]);

		time_sleep(timeStep);
	}

	gpioWrite(outport1,0);
	gpioWrite(outport2,0);
	gpioWrite(outport3,0);
	gpioWrite(outport4,0);

	gpioWrite(outport5,0);
	gpioWrite(outport6,0);
	gpioWrite(outport7,0);
	gpioWrite(outport8,0);



	/* Stop DMA, release resources */
	gpioTerminate();

	exit(0);
}


