/*
 * basicmove2.c
 *
 *  Created on: 10 Dec 2017
 *      Author: aron

Complie and linke with gcc -Wall -pthread -o basicmove2 basicmove2.c  -lrt -lm

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


static char *deviceName = "/dev/paschar";

void cleanup()
{
 // nothing to do.
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


int main(int argc, char *argv[])
{
	// ports already setup and
	int i = 0;
	int j = 0;

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
	if (argc != 3)
	{
		printf("Usage: basicMove xxx yyy \n");
		exit(1);
	}

	FILE *fp;
	fp = fopen(deviceName, "w");

	if(fp==NULL)
	{
		fprintf(stderr, "Failed to open device %s\n",deviceName);
		exit(1);
	}

	atexit(&cleanup);


	int x = atoi(argv[1]);
	int y = atoi(argv[2]);


	double dist = sqrt(x*x + y*y);

	char *buff = malloc(dist+1);

	for (i = 0;i < dist;i++)
	{
		int xoffset = mod((int)(x*i/dist) , 8);
		int yoffset = mod((int)(y*i/dist) , 8);

		char out = 0;

		for (j = 0;j < 4;j++)
		{
			out = out | ((1<<j)*seq[yoffset][j]);
		}

		for (j = 0;j < 4;j++)
		{
			out = out | ((1<<(j+4))*seq[xoffset][j]);
		}
		buff[i] = out;
	}

	// leave motors uncharged when finished.
	buff[i] = 0;

	// send it to the device driver
	int written = fwrite(buff,1,i+1,fp);

	if (written != dist+1)
	{
		fprintf(stderr, "Failed to write %d, only wrote %d\n",i+1, written);
		exit(1);
	}

	fclose(fp);

	exit(0);
}

