/*
VARSION:1
LAST_UPDATE:201607015
2016年度プログラミング応用用プログラム用関数ファイル

内容:
・音楽再生ファイル。

例外処理:

コメント:
・http://mcommit.hatenadiary.com/entry/20130220/1361286335　英語のサイト
・http://ameblo.jp/fadis/entry-10401645869.html ALSAの叩き方
・ALSAライブラリを使ってc言語でwav再生:webサイト
・イヤホンジャックでは動作しない
・コンパイル時に-lasoundオプションを必要とする

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
