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

slideWinAFlag = False



ser= serial.Serial('/dev/ttyUSB-trellis',9600,timeout=1)
ser.flushInput()

#ser1 = serial.Serial('/dev/ttyUSB-trellis',9600,timeout=1)
# ser1.flushInput()
    
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
  
  

def redWin_arduino():
    client.publish("phone/trellis/red", 1)
    print(" red <- Recieved Solved")
def redReset_arduino():
    client.publish("phone/trellis/red", 0)
    print(" red <- Recieved Reset")

def redWin_phone():
    ser.write('redSOLVED'.encode())
    print("red -> Sent Solved")
def redReset_phone():
    ser.write('redRESET'.encode())
    print("red -> Sent Reset")
       
def blueWin_arduino():
    #relay_1_Set_arduino()
    client.publish("phone/trellis/blue", 1)
    print(" blue <- Recieved Solved")
    #client.publish("phone/pots/status", "SOLVED")
def blueWin_phone():
   # ser.write('blueSOLVED'.encode())
    #lient.publish("phone/pots/status", "SOLVED")
    print("blue -> Sent Solved")
def blueReset_arduino():
    client.publish("phone/trellis/blue", 0)
    print(" blue <- Recieved Reset")
    #client.publish("phone/pots/status", "RESET")
def blueReset_phone():  
    ser.write('blueRESET'.encode())
    #client.publish("phone/pots/status", "RESET")
    print("blue -> Sent Reset")
    

    

# Callback when message is published to MQTT subscribed topic
def on_message(client, userdata, msg):
  # Print the message and topic in which it was published
  print(msg.topic + " " + str(msg.payload))
  # Change the global puzzle state based on message received
  global state
  #temp = int(msg.payload)
  temp = int(msg.payload)


#========================= TRELLIS PUZZLES ========================  
          
  if(msg.topic == "phone/trellis/blue"):    
      if(   temp == 1 ):
          blueWin_phone()
      elif( temp == 0 ):
          blueReset_phone()
              
# ----------------- LOGIC #2 - SEQUENCE -----------------
  if(msg.topic == "phone/trellis/red"):    
      if(   temp == 1 ):
          redWin_phone()          
      elif( temp == 0 ):
          redReset_phone()
          




# Callback when client is disconnected from MQTT broker
def on_disconnect(client, userdata, rc):
  client.loop_stop()


# Setup MQTT
client = MQTT.Client()
# Assign callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
# Connect to MQTT server
client.connect("10.1.10.177", 1883, 60)
# Start the MQTT update loop
client.loop_start()



print("Main Loop Start")

# Main program loop ==============================================================================================================================

while True:
    
    #print("reading serial ....")    
    

    str_read = ser.readline()
    #print("read String 1")
    newString = convertString(str_read)
    print(newString)
    
# SERIAL PORT # 1 - Circle Logic and Sequence Logic
    if(newString == "BLUE_WIN"):
        blueWin_arduino()
    elif(newString == "BLUE_RESET"):
        blueReset_arduino()
        
    elif(newString == "RED_WIN"):
        redWin_arduino()
    elif(newString == "RED_RESET"):
        redReset_arduino()

# SERIAL PORT # 2 - final Puzzle -Phases

    ser.flushInput()
    time.sleep(.5)    
# READ FROM SECOND SERIAL PORT
#     str_read2 = ser1.readline()
#     newString1 = convertString(str_read2)
#     print(newString1)
#     
# 
#     if(newString1 == "PHASE_1"):
#         client.publish("phone/final/phase_1", 1)
#         #plays sound
#     if(newString1 == "PHASE_2"):
#         client.publish("phone/final/phase_2", 1)
#     if(newString1 == "PHASE_3"):
#         client.publish("phone/final/phase_3", 1)
#     if(newString1 == "PHASE_4"):
#         client.publish("phone/final/puzzle", 1)
#     if(newString1 == "FINAL_RESET"):
#         #client.publish("phone/final/puzzle", 0)
#         client.publish("phone/final/phase_1", 0)
#         client.publish("phone/final/phase_2", 0)
#         client.publish("phone/final/phase_3", 0)
#         client.publish("phone/final/start", 0)
# 
# 
# #    ser.flushInput()
#     ser1.flushInput()
#     


 #   time.sleep(.5)
          
       
        