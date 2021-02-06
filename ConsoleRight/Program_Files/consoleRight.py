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
timeDelay=0.5
# Serial 1 - Toggle Logic
ser1 = serial.Serial('/dev/ttyUSB-toggle',9600,timeout=1)
ser1.flushInput()

ser2 = serial.Serial('/dev/ttyUSB-slidepot',9600,timeout=1)
ser2.flushInput()

ser3 = serial.Serial('/dev/ttyUSB-wire',9600,timeout=1)
ser3.flushInput()



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
  
  
def togWin_arduino():
    client.publish("phone/logic/toggle", 1)
    #print("      TOG <- Recieved Solved")
def togReset_arduino():
    client.publish("phone/logic/toggle", 0)
    #print("      TOG <- Recieved Reset")
    
def togWin_phone():    
    ser1.write('togSOLVED'.encode())
    #print("     TOG -> Sent Solved")
def togReset_phone():    
    ser1.write('togRESET'.encode())
    #print("     TOG -> Sent Reset")
    
def slideWin_arduino():
    client.publish("phone/pots/slides", 1)
    #print(" POT <- Recieved Solved")
def slideReset_arduino():
    client.publish("phone/pots/slides", 0)
    #print(" POT <- Recieved Reset")
    
def slideWin_phone():
    ser2.write('potSOLVED'.encode())
    #print("POT -> Sent Solved")  
def slideReset_phone():  
    ser2.write('potRESET'.encode())
    #print("POT -> Sent Reset")
    
    

def wireWin_arduino():
    client.publish("phone/wire", 1)
    #print(" WIRE <- Recieved Solved")
def wireReset_arduino():
    client.publish("phone/wire", 0)
    #print(" WIRE <- Recieved Reset")

def wireWin_phone():
    ser3.write('wireSOLVED'.encode())
    #print("WIRE -> Sent Solved")
def wireReset_phone():
    ser3.write('wireRESET'.encode())
    #print("WIRE -> Sent Reset")
       
    
    
 

# Callback when message is published to MQTT subscribed topic
def on_message(client, userdata, msg):
  # Print the message and topic in which it was published
  print(msg.topic + " " + str(msg.payload))
  # Change the global puzzle state based on message received
  global state
  #temp = int(msg.payload)
  temp = int(msg.payload)
  
  
  
  
  
  


#========================= LOGIC PUZZLES ========================  
# ----------------- LOGIC #1 - TOGGLE -----------------
  if(msg.topic == "phone/logic/toggle"):    
      if(   temp == 1 ):
          togWin_phone()
      elif( temp == 0 ):
          togReset_phone()
          
  elif(msg.topic == "phone/pots/slides"):    
      if(   temp == 1 ):
          slideWin_phone()      
      elif( temp == 0 ):
          slideReset_phone()  
  elif(msg.topic == "phone/wire"):    
      if(   temp == 1 ):
          wireWin_phone()      
      elif( temp == 0 ):
          wireReset_phone()  




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

while True:

# ============================ Read Serial Port #1 ============================ 
    #print("reading serial 1....")    
    str_read1 = ser1.readline()
    newString1 = convertString(str_read1)
    print(newString1)    

#----- Puzzle # 1 - TOGGLE -----  
    if(newString1 == "TOGGLE_WIN"): togWin_arduino()
    elif(newString1 == "TOGGLE_RESET"): togReset_arduino()

    ser1.flushInput()
    time.sleep(timeDelay)
 
 

# ============================ Read Serial Port #2 ============================ 
    #print("reading serial 2 ....") 
    str_read2 = ser2.readline()       
    newString2 = convertString(str_read2)
    print(newString2)
    
#----- Puzzle # 2 - SLIDE POTS -----   
    if(newString2 == "SLIDE_WIN"): slideWin_arduino()
    elif(newString2 == "SLIDE_RESET"): slideReset_arduino()  
    
    ser2.flushInput()
    time.sleep(timeDelay)
    

# ============================ Read Serial Port #3 ============================ 
    #print("reading serial 3 ....") 
    str_read3 = ser3.readline()       
    newString3 = convertString(str_read3)
    print(newString3)
    
#----- Puzzle # 3 - COLORED WIRE -----   
    if(newString3 == "WIRE_WIN"): wireWin_arduino()
    elif(newString3 == "WIRE_RESET"): wireReset_arduino()
    
    ser3.flushInput()
    time.sleep(timeDelay)
    
    
    
    
    
    
    
