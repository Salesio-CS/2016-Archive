##・概要
　黒ひげ危機一髪を電子版にしたもの。遊び方は一般的な黒ひげ危機一髪と同様で，剣を樽に刺し込み，人形が飛び出たら負けという仕様になっている。  
　プログラムでは刺した剣の感知とそれを用いての乱数発生，セーフだった場合の音声出力，飛び出す際に使用するモーターの制御を行っている。

##・開発環境
Raspberry Pi 2 Model B  
OS：Raspbian Jessie  
使用言語：C言語  
エディタ：vi  
GPIO制御に使用するライブラリ：WiringPi  
音声出力に使用するソフト：Omxplayer(Raspbianにプリインストールされている)  
  
##・ソースコードを利用するための準備(WiringPiのインストール方法)
1.以下のコマンドを使用してアップデートとアップグレードを行う。  
`sudo apt-get install update`  
`sudo apt-get upgrade`  
2.以下のコマンドを使用してgitを導入する。  
`sudo apt-get install libi2c-dev`  
`sudo apt-get install git-core`  
3.以下のコマンドを使用してWiringPiのインストールを行う。  
`git clone git://git.drogon.net/wiringPi`  
`cd wiringPi`  
`./build`  
4.以下のコマンドでインストールされているかを確認する。  
`gpio -v`  
  
##・利用手順
ターミナルで以下のコマンドを使用して実行する。  
`gpio –g mode 18 out`  
`sudo ./file-name`  

##・プログラムの仕様  
以下はプログラム内で使用したWiringPi特有の関数の解説である。  

| 使用した関数名                     | 解説                                                                           |
|:--------------------------------:|:------------------------------------------------------------------------------:|
| wiringPiSetupGpio(void)           | GPIOのピン番号を利用するための設定                                               |
| pinMode(GPIOname,INPUT or OUTPUT) | GPIOの設定を行う。INPUTはピンを入力として使用し，OUTPUTはピンを出力として使用できる。|
| digitalRead(GPIOname)             | ピンの状態を読み取る。1または0が入る。                                            |
| digitalWrite(GPIOname,0 or 1)     | ピンに1(=HIGH)または0(=LOW)を設定する。                                          |
