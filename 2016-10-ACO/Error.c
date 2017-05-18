/*
VARSION:1
LAST_UPDATE:20161022
2016年度プログラミング応用用プログラム用関数ファイル

内容:
・引数として入力されたエラー変数のエラーをstderrに出力する。

例外処理:
・なし

*/

#include"Raspi.h"

void Error(ERROR err){
  switch(err){
  case NOTHING_ERROR:
    perror("No Error.");
    break;
  case MEMORY_CANT_GET_ERROR:
    perror("malloc function can't get error.");
    break;
  case CANT_FILE_OPEN:
    perror("fopen function can't get file pointer or file descriptor.");
    break;
  case CANT_LODE_MUSIC_FILE_NAME:
    perror("Music file name is lower than define.");
    break;
  case CANT_OPEN_PCM_STREAM:
    perror("PCM stream can't open");
    break;
  case CANT_SET_PCM_DATAS:
    perror("PCM datas didn't set.");
    break;
  case CANT_RECOVER_SYSTEM_BY_PCM:
    perror("This system couldn't recover PCM system.");
    break;
  case DO_NOT_DEFINE_MUSIC_NUMBER:
    perror("didn't select music number.");
    break;
  case CANT_CREATE_PIPE_CHILD_TO_PARENT:
    perror("This system couldn't create pipe.(C2P)");
    break;
  case CANT_CREATE_PIPE_PARENT_TO_CHILD:
    perror("This system couldn't create pipe.(P2C)");
    break;
  case CANT_GET_PROCESS_ID:
    perror("can't create process.");
    break;
  case CANT_START_NEW_PROGRAM:
    perror("This system could not start Button process.");
    break;
  case CANT_WRITE_PROCESS:
    perror("can't write Button process.(Maybe broken pipe)");
    break;
  case UNKNOWN_ERROR:
    perror("Unkown Error.");
    break;
  default:
    perror("Sorry, this error is not define.Report programer");
    break;
  }
}
