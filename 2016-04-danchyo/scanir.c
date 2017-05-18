/*
* scanir.c
*
* copyright © 2016 Katsuhiko Miki All rights reserved.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#define GPIO4 0

int readable = 1;
int read_pin = 7;	//nyuryoku pin
int interval = 1;	//keizoku jikan hantei no kankaku
int max_wait = 40000;	//saidai keizoku jikan

void signalCallBackHandler(int sig)
{
	readable = 0;
}

double getMoment()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((double)(tv.tv_sec) * 1000000 + (double)(tv.tv_usec));
}


int main(int argc, char *argv[])
{

	int result=0;
	int i=0;

	// scandata kakidasi pointa syutoku
	FILE *fp;
	char *fileName = "irdata.txt";
	if (argc >= 2){ fileName = argv[1]; }
	if ((fp = fopen(fileName, "w")) == NULL){
		printf("can't open file : %s\n", fileName);
		exit(1);
	}

	printf("write file: %s\n", fileName);	//1



	if (signal(SIGINT, signalCallBackHandler) == SIG_ERR){
		printf("can't set signal\n");
		exit(1);
	}

	//wiringPi no setup
	if (wiringPiSetup() == -1){
		printf("error wiringPi setup\n");
		exit(1);
	}

	//yomitori pin number
	if (argc >= 3){
		read_pin = atoi(argv[2]);
	}

	pinMode(read_pin, INPUT);
	printf("scaning pin: %d (wiringpi)\n", read_pin);	//2


	//saidai keizoku time
	if (argc >= 4){
		max_wait = atoi(argv[3]) * 1000;
	}

	printf("max keep time: %d(ms)\n", max_wait / 1000);	//3

	//stanby OK
	printf("Infrared LED scanning start.\n");		//4
	printf("Pressed Ctrl+C, this program will exit.\n");	//5

	//scan start
	while(1){
		result = scan(fp);

		if (result || !readable){
			printf("\n\n!!! could not scanning. quit.\n\n");

		}else{
			system("bash sound.sh");
			pinMode(GPIO4, OUTPUT);
			digitalWrite(GPIO4,1);

			printf("\nScanning has been done.\n\n");
			for(i=0; i<=5; i++){
				digitalWrite(GPIO4,1);
				delay(100);
				digitalWrite(GPIO4,0);
				delay(100);
			}
	  	}
	}
fclose(fp);
}


int scan(FILE *fp)
{


	if (!digitalRead(read_pin)){ return 1; }

	int on, off;


	while (readable && digitalRead(read_pin)){} //wait for start sousin


	while (readable){ //LEDkitayo
		on = getTime(0);
		off = getTime(1);
		fprintf(fp, "%6d %6d\n", on, off);


		//saidai keizoku time to same
		if (off > max_wait){ break; }
	}

	return 0;
}



int getTime(int status)
{
	int count = 0;
	int max = max_wait / interval;
	double start, end;

	start = getMoment();
	while (digitalRead(read_pin) == status)
	{
		delayMicroseconds(interval);
		count++;
		if (count > max){ break; }
	}
	end = getMoment();

	return getInterval(start, end);
}



int getInterval(double t1, double t2)
{
 	return (int)(t2 - t1);
}

