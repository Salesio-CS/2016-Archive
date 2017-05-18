/*
VERSION:1
LAST UPDATE:2016/10/22

アップデート内容:


内容:
・プロセスから入力を受け取る

コメント:

 */
#include"Raspi.h"

ERROR GetButton(RASPI raspi){
  static FILE* fp=NULL;//ログ用ファイル
  char get;

  if(NULL==fp) if(NULL==(fp=fopen("button.log","w+"))) return CANT_FILE_OPEN;
  
  read(raspi->pipe.fd_r,&get,sizeof(char));

  switch(get){
  case 'A':
    raspi->button_input[0]=1;
    break;
  case 'B':
    raspi->button_input[1]=1;
    break;
  case 'C':
    raspi->button_input[2]=1;
    break;
  case 'D':
    raspi->button_input[3]=1;
    break;
  default:
    return UNKNOWN_ERROR;
  }

  fprintf(fp,"%c",get);
  
  return NOTHING_ERROR;
}
