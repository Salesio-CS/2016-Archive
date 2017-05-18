/*
VARSION:01
LAST_UPDATE:20160715

＜内容＞
／MS-DOSのgetchの代わり
／エラーに対応していない
 */

#include"Raspi.h"
#include<termios.h>

char getch(){
  char ch;
  struct termios x;

  //標準入力のエコーを切り、非カノニカルモードに設定
  tcgetattr(0,&x);//標準入力をtermios構造体にセット
  x.c_lflag= x.c_lflag & ~(ICANON|ECHO);//カノニカルモードを切り、エコーを抑制する
  tcsetattr(0,TCSANOW,&x);//標準入力にすぐに変更を適用

  ch=getchar();//文字を読み込み
  
  //標準入力をエコーするように設定し、カノニカルモードに設定
  x.c_lflag= x.c_lflag|(ICANON|ECHO);//カノニカルモードに設定し、エコーを再開
  tcsetattr(0,TCSANOW,&x);
  
  return ch;
  
}
