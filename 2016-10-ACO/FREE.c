/*
VARSION:1
LAST_UPDATE:20160706
2016�N�x�v���O���~���O���p�p�v���O�����p�֐��t�@�C��

���e:
�ERASPI�\���̃|�C���^�̗v�f���������
�ERASPI�\���̃|�C���^�̎��̂��������

��O����:

*/


#include"Raspi.h"

ERROR FREE(RASPI raspi){
	int i;//counter for for

	//for (i = 0; i < MUSIC_VALUE; i++) free(raspi->music_filename[i]);

	free(raspi);

	return NOTHING_ERROR;
}