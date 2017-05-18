/*
VARSION:2
LAST_UPDATE:201607015
2016年度プログラミング応用用プログラム用関数ファイル

修正内容:
・誤字の修正
・構造体の配列のサイズが違っていたことを修正(5→4)

内容:
・Waveファイルに対するデータを記述してある。

例外処理:

コメント:
・http://mcommit.hatenadiary.com/entry/20130220/1361286335　英語のサイト
・http://ameblo.jp/fadis/entry-10401645869.html ALSAの叩き方
・ALSAライブラリを使ってc言語でwav再生:webサイト
・コグノスケ ALSA　その3:webサイト

・PCM_DEVICEに設定した項目によって音楽が流れる媒体が変わる
hw:0,0などの形で渡す。/dev/sndディレクトリ内のファイルを参照するとなにが対応しているかがわかる。
＜見方＞
ファイル名例(plughw:0,0なら)：pcmC0D0p
(ファイル名の意味)
pcm:pcmで利用可能
C0:サウンドカード0
D0:デバイス0
p:再生可能機器(cならば録音可能機器)

・コンパイル時に-lasoundオプションを必要とする

*/
#ifndef _WAVE_DATA_HEADER_2016_
#define _WAVE_DATA_HEADER_2016_

#include"Raspi.h"
#include<alsa/asoundlib.h>

//PCMのデフォルト設定
#ifndef PCM_DEVICE
#define PCM_DEVICE "plughw:2,0"//サウンドデバイス
#endif

#ifndef SOFT_RESAMPLE
#define SOFT_RESAMPLE 1//alsaが再生周波数を変更することを許可するか(1=許可)
#endif

#ifndef LATENCY
#define LATENCY 50000//バッファに蓄える時間[ms]
#endif

#ifndef WAVE_FORMAT_ID
#define WAVE_FORMAT_ID 1//フォーマットID
#endif

#ifndef DEFAULT_CHANNEL
#define DEFAULT_CHANNEL 2//チャンネル数
#endif

#ifndef DEFAULT_SAMPLING_RATE
#define DEFAULT_SAMPLING_RATE 48000//デフォルトの再生周波数=48[kHz]
#endif

#ifndef DEFAULT_BIT_PER_SAMPLE
#define DEFAULT_BIT_PER_SAMPLE 16
#endif

#ifndef DEFAULT_BUFFER_SAMPLE
#define DEFAULT_BUFFER_SAMPLE 1
#endif

//wavファイル解析用構造体

//ヘッダー構造体
typedef struct d_wavheader{
  char riff[4];//riffヘッダ
  unsigned int filesize;//ファイルサイズ-8
  char wave[4];//waveヘッダ
}wavheader;

//データチャンク構造体
typedef struct d_tagchank{
  unsigned char fmt[4];//fmtチャンク
  int fmtsize;//fmtチャンクのバイト数
}tagchank;

//データフォーマット用構造体
typedef struct d_wavformat{
  unsigned short id;//フォーマットコード
  unsigned short channel;//チャンネル数
  unsigned int samplingrate;//サンプリングレート
  unsigned int bps;//byte per sec
  unsigned short blocksize;//ブロック境界
  unsigned short bpsm;//bit per sample
}wavformat;

//関数群
ERROR wavDump(const char *dumpfilename,const char *filename,wavformat* wf,int dumpflag);

#endif
