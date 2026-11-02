
#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 27
int main(int argc, char* argv[]){


	gpioInitialise();
	gpioSetMode(PIN,PI_OUTPUT);
	gpioWrite(PIN,1);
	getchar();
	gpioWrite(PIN,0);
	gpioTerminate();
	return 0;






}

