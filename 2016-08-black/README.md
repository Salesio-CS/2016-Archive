# 2016-08-black

#方法

Raspberry Pi上のgcc環境下でloopback.cppを実行

Raspberry Pi をシリアル通信が可能な状態にセットする

Raspberry PiはGPIOのRXピンをXbeeへ,TXピンをArduinoへ接続する

配線の様子↓

Xbee(TX) - (RX)Raspberry Pi

Raspberry Pi(TX) - Arduino(RX)

GNDは共通化して接続する

Arduino上で、IDEを用いてArduinoにプログラムを書き込む

コントローラーにctrl.ino

本体側Arduinoにrcv.inoを書き込む

コントローラー側と本体側のArduinoとRaspberry Piの電源を同時につけるとXbeeが自動的に接続状態となる

準備は以上となる



#######
