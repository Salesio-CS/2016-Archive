/*
MAKER:Daisuke Kuwahara
VERSION:2.0
LAST UPDATE:20161022

<update>
・commentをアップデート

<comment>
・Raspiの実行ファイルとは別にコンパイルを行うこと実行ファイル名は[GPIO]
・main.cを除いてGPIO.c GPIO.hを追加する

*/

#ifndef _GPIO_HEADER_VER_1_2016_
#define _GPIO_HEADER_VER_1_2016_

//ヘッダ読み込み部
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
//#include"WaveData.h"

//マクロ定義
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 4*1024
#endif

#ifndef PREOPHERAL_BASE
#define PERIPHERAL_BASE 0x3f000000
#endif

#ifndef GPIO_BASE
#define GPIO_BASE PERIPHERAL_BASE+0x00200000
#endif

//構造体宣言
typedef struct def_gpio{
  unsigned long gpio_base;//物理メモリアドレス
  int memory_fd;//メモリ用ファイルディスクリプタ
  void *map;//メモリマップ
  volatile unsigned int *addr;//メモリアドレス(最適化を抑制)
} Gpio;

#endif
