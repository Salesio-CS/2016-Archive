# -*- coding: utf-8 -*-
#!/usr/bin
import serial
import time
import witingpi2 as wp

SPI_SPEED = 115200
SPI_CH = 0
LED_PIN = 13

wp.wiringPiSPISetup (SPI_CH, SPI_SPEED)
wp.wiringPISetupGpio()
wp.pinMode(LED_PIN, wp.GPIO.OUTPUT)

ser = serial.Serial('/dev/ttyACM0', 115200)
control = ser.read()

if control >= 0 && control <= 2:
  wp.digitalWrite(LED_PIN, wp.GPIO.HIGH)
else :
  wp.digitalWrite(LED_PIN, wp.GPIO.LOW)
