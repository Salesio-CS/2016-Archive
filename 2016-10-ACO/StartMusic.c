/*
VARSION:1
LAST_UPDATE:201607015
2016�N�x�v���O���~���O���p�p�v���O�����p�֐��t�@�C��

���e:
�E���y�Đ��t�@�C���B

��O����:

�R�����g:
�Ehttp://mcommit.hatenadiary.com/entry/20130220/1361286335�@�p��̃T�C�g
�Ehttp://ameblo.jp/fadis/entry-10401645869.html ALSA�̒@����
�EALSA���C�u�������g����c�����wav�Đ�:web�T�C�g
�E�C���z���W���b�N�ł͓��삵�Ȃ�
�E�R���p�C������-lasound�I�v�V������K�v�Ƃ���

*/

#include"WaveData.h"

ERROR StartMusic(RASPI raspi){
  ERROR err;
  wavformat wf={
    WAVE_FORMAT_ID,
    DEFAULT_CHANNEL,
    DEFAULT_SAMPLING_RATE,
    DEFAULT_SAMPLING_RATE*DEFAULT_CHANNEL*(DEFAULT_BIT_PER_SAMPLE/8),
    (DEFAULT_BIT_PER_SAMPLE/8)*DEFAULT_CHANNEL,
    DEFAULT_BIT_PER_SAMPLE
  };

  if(raspi->music_number==-1) return DO_NOT_DEFINE_MUSIC_NUMBER;
  
  err=wavDump(raspi->dump_filename,raspi->music_filename[raspi->music_number],&wf,raspi->dumpflag);

  return err;
}
