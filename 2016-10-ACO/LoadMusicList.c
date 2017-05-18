/*
VARSION:1
LAST_UPDATE:20160706
2016年度プログラミング応用用プログラム用関数ファイル

内容:
・音楽ファイル名をraspi_musicfile.csvから読み込み
・raspi->music_filename配列に音楽ファイルの名前を代入する。

例外処理:
・ファイルが開けなかった場合CANT_FILE_OPENを返しプログラムを終了する。
・音楽ファイル名が既定の個数に達していない場合にはCANT_LODE_MUSIC_FILE_NAMEを返しプログラムを終了する。

*/

#include"Raspi.h"

ERROR LoadMusicList(RASPI raspi){
	FILE *fp;//raspi_musicfile.csvファイル用ファイルポインタ
	int i=0;//counter for for()

	//fileopen
	if (NULL == (fp = fopen("raspi_musicfile.csv", "r"))) return CANT_FILE_OPEN;

	//初めの部分のみ読み込み
	fscanf(fp, "%[^,]",raspi->music_filename[i]);

	//後の部分読み込み
	for (i = 1; i < MUSIC_VALUE; i++) if (EOF == fscanf(fp, ",%[^,]", raspi->music_filename[i])) return CANT_LODE_MUSIC_FILE_NAME;

	//fileclose
	fclose(fp);

	return NOTHING_ERROR;

}