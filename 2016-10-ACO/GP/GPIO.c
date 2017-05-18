/*
MAKER:Daisuke Kuwahara
VERSION:2.0
LAST UPDATE:20161027

<update>
・12番ポートをVCCとして使用

<内容>
・SoCのGPIOピン用レジスタ(GPIO Pin Level Registers;0x7E200034;+13)を使用してGPIOから入力を受け取る
・SoCのGPIOピン用レジスタを使用してGPIOから3.3[V]電流を流す

<comment>
・[Lチカ]Raspberry piでC言語からSoCのレジスタを操作してGPIOを制御;web site
・mmap関数:ファイルやデバイスをメモリ(void)にマップ・アンマップする

*/

#include"GPIO.h"
#include"WaveData2.h"
#include<sys/ioctl.h>
#include<termios.h>

int main(){
  Gpio gpio={GPIO_BASE};
  char flag='a';
  int flg[4]={0,0,0,0};
  volatile unsigned int *gpiomem;

  char wave_filename[4][MUSIC_FILE_NAME_SIZE]={"bell.wav","snare.wav","snare2.wav","taiko.wav"};
  wavformat wf={
    WAVE_FORMAT_ID,
    DEFAULT_CHANNEL,
    DEFAULT_SAMPLING_RATE,
    DEFAULT_SAMPLING_RATE*DEFAULT_CHANNEL*(DEFAULT_BIT_PER_SAMPLE/8),
    (DEFAULT_BIT_PER_SAMPLE/8)*DEFAULT_CHANNEL,
    DEFAULT_BIT_PER_SAMPLE
  };

  struct termio tty_backup;
  struct termio tty_change;

  ioctl(0,TCGETA,&tty_backup);
  tty_change=tty_backup;

  tty_change.c_lflag &=~(ECHO|ICANON);
  tty_change.c_cc[VMIN]=0;
  tty_change.c_cc[VTIME]=1;

  ioctl(0,TCSETAF,&tty_change);
  
  //メモリ確保部分
  
  if((gpio.memory_fd=open("/dev/mem",O_RDWR|O_SYNC))<0) return 1;//dev/memのファイルディスクリプタの確保
//should use sudo

  gpio.map=mmap(NULL,BLOCK_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,gpio.memory_fd,gpio.gpio_base);
  if(gpio.map==MAP_FAILED){
  //ttyを戻す
    fflush(NULL);
    ioctl(0,TCSETAF,&tty_backup);
    close(gpio.memory_fd);
    return 2;
  }

  gpio.addr=(volatile unsigned int *)gpio.map;//mapのアドレスを確保
  gpiomem=gpio.addr;
  gpio.addr=gpio.addr+13;//GPIO Pin Level Registersのレジスタに移動
  
  //GPIO port 12 set high
  *(gpiomem+1)=0x00000040;
  *(gpiomem+7)=0x00001000;

  //入力受け取り(プロセス間通信を行うまでの間while関数)
  while(1){
    int i;
    read(0,&flag,sizeof(char));
    if(flag=='e') break;//終了するかを確認
    
    //GPIOの入力確認
    
    if((*(gpio.addr)&0x00010000)==0x00010000 && flg[0]!=1){//GPIO16
      perror("a");
      putchar('A');
      wavDump("NO",wave_filename[0],&wf,0);
      flg[0]=1;
    }
    else if((*(gpio.addr)&0x00080000)==0x00080000 && flg[1]!=1){//GPIO19
      perror("b");
      putchar('B');
      wavDump("NO",wave_filename[1],&wf,0);
      flg[1]=1;
    }
    else if((*(gpio.addr)&0x00100000)==0x00100000 && flg[2]!=1){//GPIO20
      perror("c");
      putchar('C');
      wavDump("NO",wave_filename[2],&wf,0);
      flg[2]=1;
    }
    else if((*(gpio.addr)&0x04000000)==0x04000000 && flg[3]!=1){//GPIO26
      perror("d");
      putchar('D');
      wavDump("NO",wave_filename[3],&wf,0);
      flg[3]=1;
    }
    else for(i=0;i<4;i++) flg[i]=0;//cheak and repair
    *(gpio.addr)=*(gpio.addr)&0x04000000;
  }

  //メモリ解放
  munmap(gpio.map,BLOCK_SIZE);
  close(gpio.memory_fd);
  
  *(gpiomem+10)=0x00001000;

  //ttyを戻す
  fflush(NULL);
  ioctl(0,TCSETAF,&tty_backup);

  //終了
  return 0;
  
}
