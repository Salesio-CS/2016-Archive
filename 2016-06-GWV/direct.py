#!/usr/bin/python
#coding: utf-8

import RPi.GPIO as GPIO

#21:OL
GPIO.setmode(GPIO.BCM)
GPIO.setup(21,GPIO.OUT)
#20:OR
GPIO.setmode(GPIO.BCM)
GPIO.setup(20,GPIO.OUT)
#13:IL
GPIO.setmode(GPIO.BCM)
GPIO.setup(13,GPIO.IN)
#19:IR
GPIO.setmode(GPIO.BCM)
GPIO.setup(19,GPIO.IN)
#16:V++
GPIO.setmode(GPIO.BCM)
GPIO.setup(16,GPIO.OUT)

print '出力LはGPIO-21番(ボード上では40番)'
print '出力RはGPIO-20番(ボード上では38番)'
print 'GNDはGNDポートへ(ボード上では37番)'
print '入力LはGPIO-13番(ボード上では33番)'
print '入力RはGPIO-19番(ボード上では35番)'
print 'V++はGPIO-16番(ボード上では36番)'

i = 0

while True:
    GPIO.output(16, 1)
    
    #L
    if True == GPIO.input(13):
        GPIO.output(21, 1)
        print 'L : ON'
    else:
        GPIO.output(21, 0)
        print 'L : OFF'

    #R    
    if True == GPIO.input(19):
        GPIO.output(20, 1)
        print 'R : ON'
    else:
        GPIO.output(20, 0)
        print 'R : OFF'
        
GPIO.cleanup()
