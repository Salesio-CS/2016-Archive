/*
VARSION:1
LAST_UPDATE:20160706
2016�N�x�v���O���~���O���p�p�v���O�����p�֐��t�@�C��

���e:
�E���y�t�@�C������raspi_musicfile.csv����ǂݍ���
�Eraspi->music_filename�z��ɉ��y�t�@�C���̖��O��������B

��O����:
�E�t�@�C�����J���Ȃ������ꍇCANT_FILE_OPEN��Ԃ��v���O�������I������B
�E���y�t�@�C����������̌��ɒB���Ă��Ȃ��ꍇ�ɂ�CANT_LODE_MUSIC_FILE_NAME��Ԃ��v���O�������I������B

*/

#include"Raspi.h"

ERROR LoadMusicList(RASPI raspi){
	FILE *fp;//raspi_musicfile.csv�t�@�C���p�t�@�C���|�C���^
	int i=0;//counter for for()

	//fileopen
	if (NULL == (fp = fopen("raspi_musicfile.csv", "r"))) return CANT_FILE_OPEN;

	//���߂̕����̂ݓǂݍ���
	fscanf(fp, "%[^,]",raspi->music_filename[i]);

	//��̕����ǂݍ���
	for (i = 1; i < MUSIC_VALUE; i++) if (EOF == fscanf(fp, ",%[^,]", raspi->music_filename[i])) return CANT_LODE_MUSIC_FILE_NAME;

	//fileclose
	fclose(fp);

	return NOTHING_ERROR;

}