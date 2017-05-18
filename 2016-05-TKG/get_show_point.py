#!/usr/bin/env python
# -*- coding: utf8 -*-
import sys
import Tkinter
import serial
import time

root = Tkinter.Tk() #8行目〜51行目をループする処理
root.title(u"Pinball Game") #プログラムのタイトルを決定
root.geometry("500x500") #ウィンドウサイズを決定する

count=0 #得点変数を初期化

#リセットボタンが押されたら得点変数が初期化される処理
def reset(self):
  global count
  count=0 
  Static2.configure(text=count)
  Static2.update()

#scoreというラベルを表示する処理
Static1 = Tkinter.Label(text=u'score',font=(u'ゴシック',30))
Static1.place(x=200, y=170)
#得点を表示するラベル
Static2 = Tkinter.Label(text=u'0',font=(u'ゴシック',30))
Static2.place(x=230, y=220)

#リセットボタンの位置を設定
Button = Tkinter.Button(text=u'reset', width=50)
Button.bind("<Button-1>",reset) 
Button.pack()

#メイン部分
ser = serial.Serial('/dev/ttyACM0', 9600) #シリアル通信でArduinoと接続する
time.sleep(2) #2秒待つ
Passing_point=0 #センサーの距離変数を初期化
hoge = ser.readline() #シリアル通信で値をセンサーの値を読み取る

#無限ループ
while 1:
 hoge = ser.readline() #シリアル通信で値をセンサーの値を読み取る
 #シリアル通信で読み取った値は文字列で稀にNULLを読み取ることがあるのでそれを弾く例外処理
 try:
  Passing_point=float(hoge) #文字列をfloat型に変換する
  Static2.update() #得点表示のラベルを再描画する
  #センサーの値が6cm以下だったら5点加算される
  if Passing_point<=6.00: 
   count+=5
   Static2.configure(text=count)
  time.sleep(1)
 except:
  Static2.configure(text=count)

root.mainloop()
