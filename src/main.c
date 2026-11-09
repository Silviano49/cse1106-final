#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 27

double calcAverage(float temp[]){
   double total = 0;
   
   
   
	for(int i = 0;i < 4;i++){
	total += temp[i];
	}
return total / 4;
}


int inRange(float arr[],int warning[], float max, float min){
	 for(int i=0; i < 4;i++){
	   if (arr[i] >= min && arr[i] <= max){
		   printf("%.1f  %s\n",arr[i], "NORMAL");
		   warning[i] = 0;
		   }
	   else{
		   printf("%.1f  %s\n",arr[i], "WARNING");
		   warning[i] = 1;
		   }
	 }
	
}
void printResults(float readings[], int warnings[]){
	FILE* fptr;
	
	fptr = fopen("output.txt", "w");
	// fprintf(fptr, "TESTING\n");
	
	if (fptr == NULL){
		printf("error opening file\n");
		return;
		}
	for(int i=0;i<4;i++){
		fprintf(fptr,"%.1f  ",readings[i]);
		if(warnings[i] == 1){
			fprintf(fptr,"NORMAL\n");
			}
		else{
			fprintf(fptr,"WARNING\n");
			}
		
		}
		
	fclose(fptr);
	printf("data recorded\n");
	}
	
void led(int arr[]){
	
	for(int i=0; i < 4;i++){
	   if (arr[i] == 1){
		   gpioWrite(PIN,1);
		   }
	   else{
		   gpioWrite(PIN,0);
		   }
	}
}

int main(int argc,char** argv){

int warning[4];
float temp[4];
float average;
float max,min;

	gpioInitialise();
	gpioSetMode(PIN,PI_OUTPUT);


	printf("enter the temperatures:");
	for (int i=0; i<4;i++){
	scanf("%f",&temp[i]);
        }
	
	printf("enter a temperature range (min-max):");
	scanf("%f %f",&min, &max);
	
printf("--------\n");
printf("\nrange: %.1f - %.1f\n",min,max);

printf("the readings:");
for(int i=0; i < 4;i++){
printf(" %.1fF\n",temp[i]);
}
printf("\nthe average is: %.1f\n", calcAverage(temp));

average = calcAverage(temp);
inRange(temp,warning,max, min);

printf("\n");
led(warning);
printResults(temp,warning);

gpioTerminate();

return 0;
}
