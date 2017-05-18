/*
VARSION:0.3
LAST_UPDATE:20160814

2016�N�x�v���O���~���O���p�p�v���O�����p�w�b�_

�A�b�v�e�[�g���e:
�@�@�@�@�E�v���Z�X����p�̍\����Pipe����ъ֐��Q���`

���e�F
	�E�v���O�����S�̂̏�Ԃ��Ǘ�����\���̂��`
	�E���삷��v���O�������g�p����w�b�_�t�@�C�����W��
	�E�v���O�����Q�Ŏg�p����define�����`
	�E�e��֐��̃v���g�^�C�v���`
	�E�e��v���O�����Ŏg�p����ϐ��̒�`

�R�����g�F
        �E�R���p�C������-lm�R�}���h���K�v
*/

#ifndef _RASPI_HEADER_VARSION_0_3_
#define _RASPI_HEADER_VARSION_0_3_

//�w�b�_�t�@�C���ǂݍ��ݕ���
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

//define����`����
//���̑��w��f�[�^
#ifndef MUSIC_VALUE
#define MUSIC_VALUE 13//���y�t�@�C���̑���
#endif

#ifndef BUTTON_VALUE
#define BUTTON_VALUE 4//�{�^���̑���
#endif

#ifndef MUSIC_FILE_NAME_SIZE
#define MUSIC_FILE_NAME_SIZE 128//���y�t�@�C�����̍ő�o�C�g��
#endif

#ifndef DUMPFILE_MAX
#define DUMPFILE_MAX 30//DUMP�t�@�C�����̍ő咷
#endif

//�G���[����p��`
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

//�ϐ���`����
typedef int ERROR;

//�\���̒�`����
typedef struct pipe_default{
  int pid;
  int fd_r;
  int fd_w;
  int status;
  int value;
  char new_process_name[100];
}Pipe;

/*
progress����:
0:�v���O�����J�n����
1:���y�I�𕔕�
2:���y�Đ�����
3:�v���O�����I������
*/

typedef struct Raspi_default{
	//�t�B�[���h
	int progress;//���݂̏�
	int music_number;//���ݑI������Ă��鉹�y�̔ԍ�(�����l=-1�@�͈�[0,MUSIC_VALUE])
        int dumpflag;//wave�̃_���v�t�@�C���̐����t���O
        int button_input[BUTTON_VALUE];//button�̓��͂̎󂯎��
        char dump_filename[DUMPFILE_MAX];//dump�t�@�C���̖��O
	char music_filename[MUSIC_VALUE][MUSIC_FILE_NAME_SIZE];//���y�t�@�C���̖��O�ꗗ
        Pipe pipe;
      int mode;

	//���\�b�h
	
	ERROR (*StartMusic)(struct Raspi_default*);
        ERROR (*StartButton)(struct Raspi_default*,...);
        ERROR (*GetButton)(struct Raspi_default*);
        ERROR (*EndButton)(struct Raspi_default*);
	void (*Error)(ERROR);
	ERROR (*Free)(struct Raspi_default*);
} Raspi;

typedef Raspi *RASPI;

//�֐��v���g�^�C�v��`����
RASPI CreateRaspi(void);//�\���̂̕ϐ�������������֐�
ERROR StartMusic(RASPI);//���y�Đ��p�֐�
ERROR StartButton(RASPI,...);
ERROR GetButton(RASPI);
ERROR EndButton(RASPI);
void Error(ERROR);//�G���[�̔���������\������֐�
ERROR FREE(RASPI);//����̃|�C���^�̉���p�֐�
char getch(void);//windows MS-DOS��"conio.h"��getch()�֐��̑���

#endif//#ifndef RASPI_HEADER_VARSION_0
