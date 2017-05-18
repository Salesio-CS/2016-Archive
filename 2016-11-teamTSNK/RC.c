#include <stdio.h>
#include <stdlib.h>
#include<wiringPi.h>
#include<unistd.h>

#define MOTOROUT1 14
#define MOTOROUT2 15
#define MOTORPWN 18
#define POW 900

main(void){

char c;

  if(wiringPiSetupGpio() == -1){
    printf("setup error");
    return 1;
  }
  pinMode(MOTOROUT1,OUTPUT);
  pinMode(MOTOROUT2,OUTPUT);
  pinMode(MOTORPWN,PWM_OUTPUT);

  digitalWrite(MOTOROUT1,0);
  digitalWrite(MOTOROUT2,0);
  digitalWrite(MOTORPWN,0);


printf("w=go s=stop x=back Shift+z=exit\n");
system("stty raw");

while(1){
c=getchar();

    //printf("key=%d ",c);

    if(c == 119){
    //w
    //printf("=go ");

     digitalWrite(MOTOROUT2,0);
     digitalWrite(MOTOROUT1,1);
     pwmWrite(MOTOROUT1,POW);

    }if(c==115){
    //s
    //printf("=stop ");

     digitalWrite(MOTOROUT1,0);
     digitalWrite(MOTOROUT2,0);
     pwmWrite(MOTOROUT1,0);

    }if(c==120){
    //x
    //printf("=back ");

     digitalWrite(MOTOROUT1,0);
     digitalWrite(MOTOROUT2,1);
     pwmWrite(MOTOROUT1,POW);

    }
    if(c==90){
    //Z
    //printf("=exit \n");

     digitalWrite(MOTOROUT1,0);
     digitalWrite(MOTOROUT2,0);
     pwmWrite(MOTOROUT1,0);

    return 0;
    }
  }
}
