#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
char rcv[1];
/* UART通信 */
int fd = serialOpen("/dev/ttyAMA0",115200); //通信周波数設定
if(fd<0){ //エラー処理
printf("can not open serialport");
}

while(1){
/* 受信処理 */
while(serialDataAvail(fd)){
  rcv = serialGetchar(fd);
  fflush(stdout);
}

/* 送信処理 */
serialPuts(fd,rcv);

delay(10);
}

return 0;
}
