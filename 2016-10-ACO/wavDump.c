/*
VARSION:2
LAST_UPDATE:20160825
2016年度プログラミング応用用プログラム用関数ファイル

修正内容:
・誤字の修正

内容:
・alsaライブラリを使用し、waveファイルを再生する。

例外処理:

コメント:
・http://mcommit.hatenadiary.com/entry/20130220/1361286335　英語のサイト
・http://ameblo.jp/fadis/entry-10401645869.html ALSAの叩き方
・ALSAライブラリを使ってc言語でwav再生:webサイト
・イヤホンジャックでは動作しない
・コンパイル時に-lasoundオプションを必要とする

*/

#include"WaveData.h"

ERROR wavDump(const char *dumpfilename,const char *filename,wavformat *wf,int dumpflag){
  FILE *fp,*dumpfp;
  wavheader header;
  tagchank chank;

  int i,j;
  int dump;
  int bfs;//buffer size
  int n;

  long len;
  
  char *pcmbuffer=NULL;//pcmのバッファ領域
  snd_pcm_t *handle=NULL;

  const static snd_pcm_format_t format=SND_PCM_FORMAT_S16;//符号付き16bit

  if((fp=fopen(filename,"rb"))==NULL) return CANT_FILE_OPEN;

  //waveファイルのヘッダ情報読み込み  
  fread(&header,sizeof(wavheader),1,fp);
  //末尾文字の追加
  header.riff[4]='\0';
  header.wave[4]='\0';


  //チャンクの読み取り
  fread(&chank,sizeof(tagchank),1,fp);
  len=(long)chank.fmtsize;//fmt sizeをint型からlongにキャスト
  //末尾文字の追加
  chank.fmt[4]='\0';

  //各種フォーマットデータの読み取り
  fread(wf,sizeof(wavformat),1,fp);

  //再生設定
  bfs=DEFAULT_BUFFER_SAMPLE*(wf->bpsm/8)*wf->channel;
  pcmbuffer=(char*)malloc(bfs);

  //pcmデバイスのオープン
  snd_pcm_open(&handle,PCM_DEVICE,SND_PCM_STREAM_PLAYBACK,0);
  //pcmパラメーターの設定
  snd_pcm_set_params(handle,format,SND_PCM_ACCESS_RW_INTERLEAVED,wf->channel,wf->samplingrate,SOFT_RESAMPLE,LATENCY);
  
  //ダンプ先ファイルを開く
  if(dumpflag==1){
    if((dumpfp=fopen(dumpfilename,"w"))==NULL){
      fclose(fp);
      return CANT_FILE_OPEN;
    }
  }

  for(i=0;i<header.filesize;i+=bfs){
    if(fread(pcmbuffer,bfs,1,fp)!=1) break;

    //pcmへの書き込み
    snd_pcm_writei(handle,(const void*)pcmbuffer,DEFAULT_BUFFER_SAMPLE);

    //dumpファイルへの書き込み
    if(dumpflag==1){
      //チャンネル数=1の場合
      if(wf->channel==1){
	switch(wf->bpsm/8){
	case 1:
	  fprintf(dumpfp,"%d\n",pcmbuffer[0]);
	  break;
	  
	case 2:
	  fprintf(dumpfp,"%d\n",pcmbuffer[0]+pcmbuffer[1]*256);
	  break;
	  
	default:
	  break;
	}
      }

      //チャンネル数=2の場合
      if(wf->channel==2){
	switch(wf->bpsm/8){
	case 1:
	  fprintf(dumpfp,"%d %d\n",pcmbuffer[0],pcmbuffer[1]);
	  break;
	  
	case 2:
	  fprintf(dumpfp,"%d %d\n",pcmbuffer[0]+pcmbuffer[1]*256,pcmbuffer[2]+pcmbuffer[3]*256);
	  break;

	default:
	  break;
	}
      }
    }
  }
  snd_pcm_drain(handle);
  snd_pcm_close(handle);

  fclose(fp);

  if(dumpflag==1) fclose(dumpfp);

  free(pcmbuffer);

  return NOTHING_ERROR;
  
}
