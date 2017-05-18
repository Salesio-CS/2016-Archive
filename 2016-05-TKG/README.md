# 2016-05-TKG

## 概要

 * 距離センサーの取得と点数表示プログラム

***DEMO:***

 ![点数表示プログラム](https://github.com/Salesio-CS/2016-05-TKG/blob/master/image/get_point.gif)

## 環境

 * Python2.7
 * Tkinter
 * pyserial
 * Arduino 1.6.9

## 環境導入

1. 自分のPCからcloneで全てのリポジトリをダウンロードする。

  ```
  $ git clone https://github.com/Salesio-CS/2016-05-TKG.git
  ```

2. ファイル内の*Ardiono.ino*をArdionoに転送する。
3. ArduinoとRaspberryをUSBケーブル(A-Bタイプ)で接続する。
4. 先ほどダウンロードしたファイルの*get_show_point.py*をRaspberry piにUSBメモリなどで転送する。
5. Raspberry piのターミナルを開き、以下のコマンドを入力しPythonの環境を構築する。

  ```
  $ pip install pyserial
  $ sudo apt-get -y install python-tk
  ```
  
## 利用方法

 * get_show_point.pyをカレントディレクトリに置き、以下のコマンドを入力する。

  ```
  $ python get_show_point.py
  ```

## 開発者

[小宮達也](https://twitter.com/remonsama)
