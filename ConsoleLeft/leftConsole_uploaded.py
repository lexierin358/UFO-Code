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



ser= serial.Serial('/dev/ttyUSB-mega',9600,timeout=1)
ser.flushInput()

ser1 = serial.Serial('/dev/ttyUSB-finale',9600,timeout=1)
ser1.flushInput()
    
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
  
  
def testWin_arduino():
    client.publish("phone/logic/test", 1)
    print("      Test Win")
def testReset_arduino():
    client.publish("phone/logic/test", 0)
    print("      Test Reset")

def togWin_arduino():
    client.publish("phone/logic/toggle", 1)
    print("      TOG <- Recieved Solved")
def togReset_arduino():
    client.publish("phone/logic/toggle", 0)
    print("      TOG <- Recieved Reset")
    
def togWin_phone():
    ser.write('togSOLVED'.encode())
    print("     TOG -> Sent Solved")
    #client.publish("phone/logic/togStatus", "SOLVED")    
def togReset_phone():
    ser.write('togRESET'.encode())
    print("     TOG -> Sent Reset")
    #client.publish("phone/logic/togStatus", "RESET")
    
    
def seqWin_arduino():
    client.publish("phone/logic/sequence", 1)
    print("      SEQ <- Recieved Solved")
def seqReset_arduino():
    client.publish("phone/logic/sequence", 0)
    print("      SEQ <- Recieved Reset")
    
def seqWin_phone():
    ser1.write('seqSOLVED'.encode())
    print("     SEQ -> Sent Solved")
def seqReset_phone():
    ser1.write('seqRESET'.encode())
    print("     SEQ -> Sent Reset")
    
    

def cirWin_arduino():
    client.publish("phone/logic/circlePuz", 1)
    print(" CIR <- Recieved Solved")
def cirReset_arduino():
    client.publish("phone/logic/circlePuz", 0)
    print(" CIR <- Recieved Reset")

def cirWin_phone():
    ser1.write('cirSOLVED'.encode())
    print("CIR -> Sent Solved")
def cireReset_phone():
    ser1.write('cirRESET'.encode())
    print("CIR -> Sent Reset")
    
    

def wireWin_arduino():
    client.publish("phone/wire", 1)
    print(" WIRE <- Recieved Solved")
def wireReset_arduino():
    client.publish("phone/wire", 0)
    print(" WIRE <- Recieved Reset")

def wireWin_phone():
    ser.write('wireSOLVED'.encode())
    print("WIRE -> Sent Solved")
def wireReset_phone():
    ser.write('wireRESET'.encode())
    print("WIRE -> Sent Reset")
       
def slideWin_arduino():
    #relay_1_Set_arduino()
    client.publish("phone/pots/slides", 1)
    print(" POT <- Recieved Solved")
    #client.publish("phone/pots/status", "SOLVED")
def slideWin_phone():
    ser.write('potSOLVED'.encode())
    #lient.publish("phone/pots/status", "SOLVED")
    print("POT -> Sent Solved")
def slideReset_arduino():
    client.publish("phone/pots/slides", 0)
    print(" POT <- Recieved Reset")
    #client.publish("phone/pots/status", "RESET")
def slideReset_phone():  
    ser.write('potRESET'.encode())
    #client.publish("phone/pots/status", "RESET")
    print("POT -> Sent Reset")
    
    
def relay_1_Set_arduino():
    client.publish("phone/relays/relay_1", 1)
    print("      SEQ <- Recieved Solved")
def relay_1_Reset_arduino():
    client.publish("phone/relays/relay_1", 0)
    print("      SEQ <- Recieved Reset")
    
def relay_1_Set_phone():
    ser1.write('setR_1'.encode())
    ser.write('setR_1'.encode())
    
    print("     RELAY -> Sent Solved")
def relay_1_Reset_phone():
    ser1.write('resetR_1'.encode())
    ser.write('resetR_1'.encode())
    #print("     SEQ -> Sent Reset")

    

# Callback when message is published to MQTT subscribed topic
def on_message(client, userdata, msg):
  # Print the message and topic in which it was published
  print(msg.topic + " " + str(msg.payload))
  # Change the global puzzle state based on message received
  global state
  #temp = int(msg.payload)
  temp = int(msg.payload)


#========================= LOGIC PUZZLES ========================  
          
  if(msg.topic == "phone/logic/circlePuz"):    
      if(   temp == 1 ):
          cirWin_phone()
      elif( temp == 0 ):
          cirReset_phone()
              
# ----------------- LOGIC #2 - SEQUENCE -----------------
  if(msg.topic == "phone/logic/sequence"):    
      if(   temp == 1 ):
          seqWin_phone()          
      elif( temp == 0 ):
          seqReset_phone()
          

#========================= FINAL PUZZLE========================
          
  if(msg.topic == "phone/final/start"):    
      if(   temp == 1 ):
          pass
          #ser1.write('startFINAL'.encode())
      elif( temp == 0 ):
          pass
          
  if(msg.topic == "phone/final/phase_1"):    
      if(   temp == 1 ):
          ser1.write('1_DONE'.encode())
          #tells arduino phase 1 is done
      elif( temp == 0 ):
          pass
              
# ----------------- LOGIC #2 - SEQUENCE -----------------
  if(msg.topic == "phone/final/phase_2"):    
      if(   temp == 1 ):
          ser1.write('2_DONE'.encode())
      elif( temp == 0 ):
          pass
        
  if(msg.topic == "phone/final/phase_3"):    
      if(   temp == 1 ):
          ser1.write('3_DONE'.encode())
      elif( temp == 0 ):
          pass
        
  if(msg.topic == "phone/final/puzzle"):    
      if(   temp == 1 ):
          ser1.write('winFINAL'.encode())
      elif( temp == 0 ):
          ser1.write('resetFinal'.encode())



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
    if(newString == "SEQUENCE_WIN"):
        seqWin_arduino()
    elif(newString == "SEQUENCE_RESET"):
        seqReset_arduino()
        
    elif(newString == "CIRCLE_WIN"):
        cirWin_arduino()
    elif(newString == "CIRCLE_RESET"):
        cirReset_arduino()

# SERIAL PORT # 2 - final Puzzle -Phases

    ser.flushInput()
    time.sleep(.5)    
# READ FROM SECOND SERIAL PORT
    str_read2 = ser1.readline()
    newString1 = convertString(str_read2)
    print(newString1)
    

    if(newString1 == "PHASE_1"):
        client.publish("phone/final/phase_1", 1)
        #plays sound
    if(newString1 == "PHASE_2"):
        client.publish("phone/final/phase_2", 1)
    if(newString1 == "PHASE_3"):
        client.publish("phone/final/phase_3", 1)
    if(newString1 == "PHASE_4"):
        client.publish("phone/final/puzzle", 1)
    if(newString1 == "FINAL_RESET"):
        #client.publish("phone/final/puzzle", 0)
        client.publish("phone/final/phase_1", 0)
        client.publish("phone/final/phase_2", 0)
        client.publish("phone/final/phase_3", 0)
        client.publish("phone/final/start", 0)


#    ser.flushInput()
    ser1.flushInput()
    


    time.sleep(.5)
          
       
        