#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<wiringPi.h>

//使用するGPIOの宣言
#define OUT_PIN 18 //GPIO18(出力)
#define GPIO21 21 //GPIO21
#define GPIO20 20 //GPIO20
#define GPIO26 26 //GPIO26
#define GPIO16 16 //GPIO16
#define GPIO19 19 //GPIO19
#define GPIO13 13 //GPIO13
#define GPIO12 12 //GPIO12
#define GPIO22 22 //GPIO22
#define GPIO27 27 //GPIO27
#define GPIO25 25 //GPIO25
#define GPIO24 24 //GPIO24
#define GPIO23 23 //GPIO23

//wiringPiで使用されているGPIOの番号の設定
int wiringPiSetupGpio(void);
void OUT_PIN1();
void OUT_PIN0();

//回数カウント用の変数
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0;　
int main(int argc,char *argv[]){
//ピンのモード設定 INPUT=入力 OUTPUT=出力
  pinMode(GPIO21,INPUT); 
  pinMode(GPIO20,INPUT);
  pinMode(GPIO26,INPUT);
  pinMode(GPIO16,INPUT);
  pinMode(GPIO19,INPUT);
  pinMode(GPIO13,INPUT);
  pinMode(GPIO12,INPUT);
  pinMode(GPIO22,INPUT);
  pinMode(GPIO27,INPUT);
  pinMode(GPIO25,INPUT);
  pinMode(GPIO24,INPUT);
  pinMode(GPIO23,INPUT);
  pinMode(OUT_PIN,OUTPUT);
  
 //ピンの状態を代入する変数 0または1が入る
  int sw21,sw20,sw26,sw16,sw19,sw13,sw12,sw22,sw27,sw25,sw24,sw23; 
  
 //GPIO設定でのエラー処理
  if(wiringPiSetupGpio() == -1){
   return 1;
  }
  
//判定を行う為に無限ループさせる
  while(1){
   //乱数生成
   srand((unsigned)time(NULL));
  
   //ピンの状態をswに代入
   sw21 = digitalRead(GPIO21); 
   sw20 = digitalRead(GPIO20);
   sw26 = digitalRead(GPIO26);
   sw16 = digitalRead(GPIO16);
   sw19 = digitalRead(GPIO19);
   sw13 = digitalRead(GPIO13);
   sw12 = digitalRead(GPIO12);
   sw22 = digitalRead(GPIO22);
   sw27 = digitalRead(GPIO27);
   sw25 = digitalRead(GPIO25);
   sw24 = digitalRead(GPIO24);
   sw23 = digitalRead(GPIO23);
   
   //ピンの状態の確認
   printf("sw21  %d\n",sw21); 
   printf("sw20  %d\n",sw20);
   printf("sw26  %d\n",sw26);
   printf("sw16  %d\n",sw16);
   printf("sw19  %d\n",sw19);
   printf("sw13  %d\n",sw13);
   printf("sw12  %d\n",sw12);
   printf("sw22  %d\n",sw22);
   printf("sw27  %d\n",sw27);
   printf("sw25  %d\n",sw25);
   printf("sw24  %d\n",sw24);
   printf("sw23  %d\n",sw23);
   printf("\n"); 
   
   //sw=0の時は出力なし sw=1のときは出力あり
   if(sw21==0){
     OUT_PIN1();
   }else{
     OUT_PIN0();
     a++; //剣で刺された回数のカウント
   }
   delay(10);
   //以下上記と同じ処理
   if(sw20==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      b++;
   }
    delay(10);
   
   if(sw26==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      c++;
   }
    delay(10);
   
   if(sw16==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      d++;
   }
    delay(10);
   
   if(sw19==0){
      OUT_PIN1();
    }else{
     OUT_PIN0();
     e++;
   }
    delay(10);
   
   if(sw13==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      f++;
   }
    delay(10);
   
   if(sw12==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      g++;
   }
    delay(10);
   
   if(sw22==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      h++;
   }
    delay(10);
   
   if(sw27==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      i++;
   }
    delay(10);
   
   if(sw25==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      j++;
   }
    delay(10);
   
   if(sw24==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      k++;
   }
    delay(10);
   
   if(sw23==0){
      OUT_PIN1();
    }else{
      OUT_PIN0();
      l++;
   }
    delay(10);
  

  //printf("%d %d %d %d %d %d %d %d %d %d %d %d\n",a,b,c,d,e,f,g,h,i,j,k,l);
  }

  return  0;
}

//押されていないとき
void OUT_PIN1(){
  digitalWrite(OUT_PIN,0);
  delay(10);
}

//押されたとき
void OUT_PIN0(){
 system("omxplayer -o local ./pong.wav");//音声再生
  int ran=14;
  int borbo=rand()%100+1;//乱数生成

  if(borbo < ran){//生成された乱数が14以下のとき当たり
    if(a==1 || b==1 || c==1 || d==1 || e==1 || f==1 || g==1 || h==1 || i==1 || j==1 || k==1 || l==1){
    printf("hoge\n");
    
    system("omxplayer -o local ./hazure.wav"); 
    digitalWrite(OUT_PIN,1);//出力
    delay(800);
    digitalWrite(OUT_PIN,0);
    delay(15000);//剣を抜き差しする時間
    a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0; //ピンの初期化
    //delay(20000);
    delay(2000);
    } 
  }
  
  //2回以上押されたとき   
  if(a>=2 && b>=2 && c>=2 && d>=2 && e>=2 && f>=2 && g>=2 && h>=2 && i>=2 && j>=2 && k>=2 && l>=2 ){
    //printf("hoge2\n"); 
    system("omxplayer -o local ./pong.wav");
    digitalWrite(OUT_PIN,1);
    delay(800);
    digitalWrite(OUT_PIN,0);
    delay(15000);
    a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0;
    delay(2000);
   } 
}
