# -*- coding:utf-8 -*-
import sys
import serial
import os
import time
import datetime
import socket

host = "192.168.0.2"
port = 30200

com = serial.Serial('/dev/ttyAMA0', 57600, timeout = 10)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
s.listen(4)

print ("wait")
#client, clientaddress = s.accept()

while True:
    client, clientaddress = s.accept()
    rmsg = client.recv(1024)
    if rmsg != '':
        print (rmsg)
    if rmsg == 'RUN':
        com.write("#M1")
    if rmsg == 'STOP':
        com.write("#M0")
    client.close()
