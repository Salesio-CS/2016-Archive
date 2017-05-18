/*
VARSION:1
LAST_UPDATE:20161019

2016年度プログラミング応用用プログラム用ヘッダ

アップテート内容:

内容：
・ボタン用プロセスに終了要求を送る。

コメント：

*/
#include"Raspi.h"
#include"pipe.h"

ERROR EndButton(RASPI raspi){
  if(-1==write(raspi->pipe.fd_w,"e",sizeof(char))){
    char command[100];

    sprintf(command,"kill %d",raspi->pipe.pid);
    system(command);
    return CANT_WRITE_PROCESS;
  }
  return NOTHING_ERROR;
}
