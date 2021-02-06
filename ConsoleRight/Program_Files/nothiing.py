# EDITED: 8-29-20
import serial
import os
import time
#import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.client as MQTT # For MQTT publish/subscribe
import RPi.GPIO as GPIO # For input/output
#from tkinter import *

import pygame.mixer
from sys import exit

import pygame, sys
from pygame.locals import *

#slideWinAFlag = False



#pygame.init()

#import signal




#ser = serial.Serial('/dev/ttyUSB-wire',9600,timeout=1)
#ser = serial.Serial('/dev/ttyUSB-toggle',9600,timeout=1)
#ser = serial.Serial('/dev/ttyUSB-finale',9600,timeout=1)
#ser1 = serial.Serial('/dev/ttyACM0',9600,timeout=.1)
#ser1 = serial.Serial('/dev/ttyUSB-mega',9600,timeout=1)
#ser1 = serial.Serial('/dev/ttyUSB-finale',9600,timeout=1)
##ser1.flushInput()
    
def printString( str ):
   #"This prints a passed string into this function"
    length = len(str)
    for x in range (length):
        print(x , " is " , (str[x]))
    return;

def convertString(str ):
   #"This take in a string of ASCII chars, converts to Chars and strips last 2 elements"
    stringLen = len(str)
    realLen = stringLen - 2
    
    tempStr = ""
    
    for x in range (realLen):
        temp = chr(str[x])
        tempStr = tempStr + temp
    str = tempStr
    return str;
#read from Arduino
# Callback after connecting to MQTT server
def on_connect(self, client, userdata, rc):
  print("Connected!")
  print("Subscribing to ToDevice/All")
  self.subscribe("ToDevice/All")
  print("Subscribing to ToDevice/1")
  self.subscribe("phone/#")
  print("Subscribing to phone")
  

 

# Callback when message is published to MQTT subscribed topic
def on_message(client, userdata, msg):
  # Print the message and topic in which it was published
  print(msg.topic + " " + str(msg.payload))
  # Change the global puzzle state based on message received
  global state
  #temp = int(msg.payload)
  temp = int(msg.payload)
  
  
  
  
  
  




# Callback when client is disconnected from MQTT broker
def on_disconnect(client, userdata, rc):
    notConnected = True
    try:
        client.connect("10.1.10.177", 1883, 60)
        notConnected = False
    except:
        time.sleep(1)
        notConnected = True
  #client.loop_stop()


# Setup MQTT
client = MQTT.Client()
# Assign callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
# Connect to MQTT server
#client.connect("10.0.0.142", 1883, 60)
notConnected = True
try:
    client.connect("10.1.10.177", 1883, 60)
    notConnected = False
except:
    time.sleep(1)
    notConnected = True
    
#client.connect("10.1.10.177", 1883, 60)
    
# Start the MQTT update loop
client.loop_start()



print("Main Loop Start")

# Main program loop ==============================================================================================================================



def newMain():
    while True:
        time.sleep(500)

if __name__ == '__main__':
    newMain()


