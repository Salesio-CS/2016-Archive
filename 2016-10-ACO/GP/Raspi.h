/*
VARSION:0.3
LAST_UPDATE:20160814

2016年度プログラミング応用用プログラム用ヘッダ

アップテート内容:
　　　　・プロセス分岐用の構造体Pipeおよび関数群を定義

内容：
	・プログラム全体の状態を管理する構造体を定義
	・動作するプログラムが使用するヘッダファイルを集約
	・プログラム群で使用するdefine文を定義
	・各種関数のプロトタイプを定義
	・各種プログラムで使用する変数の定義

コメント：
        ・コンパイル時に-lmコマンドが必要
*/

#ifndef _RASPI_HEADER_VARSION_0_3_
#define _RASPI_HEADER_VARSION_0_3_

//ヘッダファイル読み込み部分
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

//define文定義部分
//その他指定データ
#ifndef MUSIC_VALUE
#define MUSIC_VALUE 13//音楽ファイルの総数
#endif

#ifndef BUTTON_VALUE
#define BUTTON_VALUE 4//ボタンの総数
#endif

#ifndef MUSIC_FILE_NAME_SIZE
#define MUSIC_FILE_NAME_SIZE 128//音楽ファイル名の最大バイト数
#endif

#ifndef DUMPFILE_MAX
#define DUMPFILE_MAX 30//DUMPファイル名の最大長
#endif

//エラー判定用定義
#ifndef NOTHING_ERROR
#define NOTHING_ERROR 0x00000000
#endif

#ifndef MEMORY_CANT_GET_ERROR
#define MEMORY_CANT_GET_ERROR 0x00000001
#endif

#ifndef CANT_FILE_OPEN
#define CANT_FILE_OPEN 0x00000002
#endif

#ifndef CANT_LODE_MUSIC_FILE_NAME
#define CANT_LODE_MUSIC_FILE_NAME 0x00000003
#endif

#ifndef CANT_OPEN_PCM_STREAM
#define CANT_OPEN_PCM_STREAM 0x00000004
#endif

#ifndef CANT_SET_PCM_DATAS
#define CANT_SET_PCM_DATAS 0x00000005
#endif

#ifndef CANT_RECOVER_SYSTEM_BY_PCM
#define CANT_RECOVER_SYSTEM_BY_PCM 0x00000006
#endif

#ifndef DO_NOT_DEFINE_MUSIC_NUMBER
#define DO_NOT_DEFINE_MUSIC_NUMBER 0x00000007
#endif

#ifndef CANT_CREATE_PIPE_CHILD_TO_PARENT
#define CANT_CREATE_PIPE_CHILD_TO_PARENT 0x00000008
#endif

#ifndef CANT_CREATE_PIPE_PARENT_TO_CHILD
#define CANT_CREATE_PIPE_PARENT_TO_CHILD 0x00000009
#endif

#ifndef CANT_GET_PROCESS_ID
#define CANT_GET_PROCESS_ID 0x0000000a
#endif

#ifndef CANT_START_NEW_PROGRAM
#define CANT_START_NEW_PROGRAM 0x0000000b
#endif

#ifndef CANT_WRITE_PROCESS
#define CANT_WRITE_PROCESS 0x0000000c
#endif

#ifndef CHILD_END
#define CHILD_END 0x0000000e
#endif

#ifndef UNKNOWN_ERROR
#define UNKNOWN_ERROR 0x0000000d
#endif

//変数定義部分
typedef int ERROR;

//構造体定義部分
typedef struct pipe_default{
  int pid;
  int fd_r;
  int fd_w;
  int status;
  int value;
  char new_process_name[100];
}Pipe;

/*
progress説明:
0:プログラム開始部分
1:音楽選択部分
2:音楽再生部分
3:プログラム終了部分
*/

typedef struct Raspi_default{
	//フィールド
	int progress;//現在の状況
	int music_number;//現在選択されている音楽の番号(初期値=-1　範囲[0,MUSIC_VALUE])
        int dumpflag;//waveのダンプファイルの生成フラグ
        int button_input[BUTTON_VALUE];//buttonの入力の受け取り
        char dump_filename[DUMPFILE_MAX];//dumpファイルの名前
	char music_filename[MUSIC_VALUE][MUSIC_FILE_NAME_SIZE];//音楽ファイルの名前一覧
        Pipe pipe;
      int mode;

	//メソッド
	
	ERROR (*StartMusic)(struct Raspi_default*);
        ERROR (*StartButton)(struct Raspi_default*,...);
        ERROR (*GetButton)(struct Raspi_default*);
        ERROR (*EndButton)(struct Raspi_default*);
	void (*Error)(ERROR);
	ERROR (*Free)(struct Raspi_default*);
} Raspi;

typedef Raspi *RASPI;

//関数プロトタイプ定義部分
RASPI CreateRaspi(void);//構造体の変数を初期化する関数
ERROR StartMusic(RASPI);//音楽再生用関数
ERROR StartButton(RASPI,...);
ERROR GetButton(RASPI);
ERROR EndButton(RASPI);
void Error(ERROR);//エラーの発生原因を表示する関数
ERROR FREE(RASPI);//楮遺体ポインタの解放用関数
char getch(void);//windows MS-DOSの"conio.h"のgetch()関数の代わり

#endif//#ifndef RASPI_HEADER_VARSION_0
