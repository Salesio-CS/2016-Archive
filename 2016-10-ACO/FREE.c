/*
VARSION:1
LAST_UPDATE:20160706
2016年度プログラミング応用用プログラム用関数ファイル

内容:
・RASPI構造体ポインタの要素を解放する
・RASPI構造体ポインタの実体を解放する

例外処理:

*/


#include"Raspi.h"

ERROR FREE(RASPI raspi){
	int i;//counter for for

	//for (i = 0; i < MUSIC_VALUE; i++) free(raspi->music_filename[i]);

	free(raspi);

	return NOTHING_ERROR;
}