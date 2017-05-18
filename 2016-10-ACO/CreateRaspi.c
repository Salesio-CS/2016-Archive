/*
VERSION:4
LAST UPDATE:2016/10/25

アップデート内容:
・raspi->pipe.new_process_nameの定義

内容:
・RASPI構造体のポインタを返す
・構造体のフィールドの初期化とメモリ確保を行う
・構造体のメソッド部分の関数ポインタに対するリンクを行う

例外処理:
・例外発生時にはNULLを返す

コメント:

 */

#include"Raspi.h"

RASPI CreateRaspi(){
  RASPI raspi;
  int i;
  //メモリ確保部分
  if (NULL == (raspi = (RASPI)calloc(1,sizeof(Raspi)))){
    return NULL;
  }

  //raspi.music_filenameのメモリ確保
  /*
  for (i = 0; i < MUSIC_VALUE; i++){
    if (NULL == (raspi->music_filename[i] = (char*)malloc(sizeof(char)*(MUSIC_FILE_NAME_SIZE + 1)))){
      return NULL;
    }
  }
  */

  //構造体要素初期化部分
  raspi->progress = 0;
  raspi->music_number = -1;
  raspi->dumpflag=1;

  raspi->pipe.pid=-1;
  raspi->pipe.fd_r=-1;
  raspi->pipe.fd_w=-1;
  raspi->pipe.status=-1;
  raspi->pipe.value=0;
  
  sprintf(raspi->pipe.new_process_name,"GPIO");
  sprintf(raspi->dump_filename,"dumpfile.dump");

  //関数リンク部分
  raspi->StartMusic=&StartMusic;
  raspi->StartButton=&StartButton;
  raspi->GetButton=&GetButton;
  raspi->EndButton=&EndButton;
  raspi->Error=&Error;
  raspi->Free=&FREE;

  return raspi;
}
