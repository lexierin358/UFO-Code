from subprocess import call

import serial
import os
import time
#import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.client as MQTT # For MQTT publish/subscribe
import RPi.GPIO as GPIO # For input/output


import pygame.mixer
from sys import exit

import pygame, sys
from pygame.locals import *

#espeak "What's up"
#call(['espeak "Sound Cards Ready" 2>/dev/null'], shell=True)

pygame.init()
#import signal

ser = serial.Serial('/dev/ttyACM0',9600)

pygame.mixer.init(48000, -16, 1, 1024)

puzzle = "stand1"
difficulty = "hard"
#os.system('mpg123 -q EyeOfTheTiger.mp3 &')

##------------------------BUTTONS-------------------------

GPIO.setmode(GPIO.BCM)
## Raspberry Pi GPIO Pins: 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
buttPins = [ 17 , 27 , 6 , 5 , 22 , 27 , 17 , 4 , 16 , 12 , 25 , 24 , 23 ]

buttonPin = [ 26 , 13 , 6 , 5 , 22 ]

numButt = len(buttPins)
numButtons = 5

buttonState = [0] * numButtons
buttonFlag = [0] * numButtons
buttonPin = [0] * numButtons
buttonBuff = [0] * numButtons

GPIO.setwarnings(False)

#for x in range(numButtons):
for x in range(numButtons):
    temp = x
    buttonPin[temp] = buttPins[temp]
    GPIO.setup( buttonPin[x] , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    buttonState[x] = 0
    buttonFlag[x] = 0

##------------------------ END-BUTTONS-------------------------

##------------------------ GLOBALS -------------------------
gotInput = 0
inputFlag = 0

if ( puzzle == "stand2"):
    #call(['espeak "Sound Card 1 Ready" 2>/dev/null'], shell=True)
# ------ SOUND CARD BOX 1 -----
    if ( difficulty == "hard" ):
        sndA = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Thunder.wav")
        sndB = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Waves.wav")
        sndC = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Sheep.wav")
        sndD = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Train.wav")
        sndE = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Saw.wav")
    
    elif ( difficulty == "easy" ):
        sndA = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Thunder.wav")
        sndB = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Waves.wav")
        sndC = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Sheep.wav")
        sndD = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Train.wav")
        sndE = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Saw.wav")
    
elif (puzzle == "stand1"):
    #call(['espeak "Sound Card 2 Ready" 2>/dev/null'], shell=True)
# ------ SOUND CARD BOX 2 -----
    if ( difficulty == "hard" ):
        sndA = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Heartbeat.wav")
        sndB = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Jet.wav")    
        sndC = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Tractor.wav")
        sndD = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Rain.wav")
        sndE = pygame.mixer.Sound("/home/pi/Desktop/shorterSounds/Horn.wav")
        
    elif ( difficulty == "easy" ):
        sndA = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Heartbeat.wav")
        sndB = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Jet.wav")    
        sndC = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Tractor.wav")
        sndD = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/LightRain.wav")
        sndE = pygame.mixer.Sound("/home/pi/Desktop/SoundCardStands/programSounds/Horn.wav")
        
    


soundChannelA = pygame.mixer.Channel(1)
#soundChannelB = pygame.mixer.Channel(2)

volNum = sndB.get_volume()
#print(volNum)

butDelay = 0.1

## ------------------------------ DEFINES ------------------------------
## ------------ BUTTON DEF ----------
def buttonDelay():
    time.sleep(butDelay)
    
def printString( str ):
   #"This prints a passed string into this function"
    length = len(str)
    for x in range (length):
        print(x , " is " , (str[x]))
    return;

def convertString( str ):
   #"This take in a string of ASCII chars, converts to Chars and strips last 2 elements"
    stringLen = len(str)
    realLen = 0
    realLen = stringLen - 2
    
    tempStr = ""
    
    for x in range (realLen):
        #print(x , " is " , (str_read1[x]))
        try:
            temp = chr(str[x])
            #print(x , " is " , temp)
            tempStr = tempStr + temp
        except:
            print("The value is not a Integer")
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
  call(['espeak "Sound Card Stand 2" 2>/dev/null'], shell=True)

# Callback when message is published to MQTT subscribed topic
def on_message(client, userdata, msg):
  # Print the message and topic in which it was published
  print(msg.topic + " " + str(msg.payload))
  # Change the global puzzle state based on message received
  global state
  #temp = int(msg.payload)
  temp = int(msg.payload)

 
#========================= SOUND CARD STAND # 1 ========================
  if( puzzle == "stand1"):
      if(msg.topic == "phone/box1/sc1"):
        
          if( temp == 0 ):
            print("Sound Card 1 - Removed")
            ser.write('1out'.encode())
            #ser.write('0')
        
          elif(temp == 1 ):
            print("Sound Card 1 - Inserted")
            ser.write('1in'.encode())
            #ser.write('1') 

      elif(msg.topic == "phone/box1/sc2"):
        
          if( temp == 0 ):
            print("Sound Card 2 - Removed")
            ser.write('2out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 2 - Inserted")
            ser.write('2in'.encode())
            
      elif(msg.topic == "phone/box1/sc3"):
        
          if( temp == 0 ):
            print("Sound Card 3 - Removed")
            ser.write('3out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 3 - Inserted")
            ser.write('3in'.encode())
            
      elif(msg.topic == "phone/box1/sc4"):
        
          if( temp == 0 ):
            print("Sound Card 4 - Removed")
            ser.write('4out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 4 - Inserted")
            ser.write('4in'.encode())
            
      elif(msg.topic == "phone/box1/sc5"):
        
          if( temp == 0 ):
            print("Sound Card 5 - Removed")
            ser.write('5out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 5 - Inserted")
            ser.write('5in'.encode())
            
      elif(msg.topic == "phone/box1/red"):        
          if( temp == 0 ):
            ser.write('RED_RESET'.encode())
        
          elif(temp == 1 ):
            ser.write('RED_PRESS'.encode())
            
#========================= SOUND CARD STAND # 1 ========================
  elif (puzzle == "stand2"):
      if(msg.topic == "phone/box2/sc1"):
        
          if( temp == 0 ):
            print("Sound Card 1 - Removed")
            ser.write('1out'.encode())
            #ser.write('0')
        
          if(temp == 1 ):
            print("Sound Card 1 - Inserted")
            ser.write('1in'.encode())
            #ser.write('1') 

      elif(msg.topic == "phone/box2/sc2"):
        
          if( temp == 0 ):
            print("Sound Card 2 - Removed")
            ser.write('2out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 2 - Inserted")
            ser.write('2in'.encode())
            
      elif(msg.topic == "phone/box2/sc3"):
        
          if( temp == 0 ):
            print("Sound Card 3 - Removed")
            ser.write('3out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 3 - Inserted")
            ser.write('3in'.encode())
            
      elif(msg.topic == "phone/box2/sc4"):
        
          if( temp == 0 ):
            print("Sound Card 4 - Removed")
            ser.write('4out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 4 - Inserted")
            ser.write('4in'.encode())
            
      elif(msg.topic == "phone/box2/sc5"):
        
          if( temp == 0 ):
            print("Sound Card 5 - Removed")
            ser.write('5out'.encode())
        
          elif(temp == 1 ):
            print("Sound Card 5 - Inserted")
            ser.write('5in'.encode())
            
      elif(msg.topic == "phone/box2/red"):        
          if( temp == 0 ):
            ser.write('RED_RESET'.encode())
        
          elif(temp == 1 ):
            ser.write('RED_PRESS'.encode())

def on_disconnect(client, userdata, rc):
    
  #client.loop_stop()
    notConnected = True
    while(notConnected):
        try:
            client.connect("10.1.10.177", 1883, 60)
            notConnected = False
        except:
            time.sleep(2)
            notConnected = True

# Global variables
#prevInput = 0
#state = 0
#prevState = 0

# Setup MQTT
client = MQTT.Client()
# Assign callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
# Connect to MQTT server

notConnected = True
while(notConnected):
    try:
        client.connect("10.1.10.177", 1883, 60)
        notConnected = False
    except:
        time.sleep(2)
        notConnected = True
#client.connect("10.1.10.177", 1883, 60)
# Start the MQTT update loop
client.loop_start()
#soundChannelA.play(sndA)
# Main program loop
while True: # main game loop
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
# ========================================== SOUND CODE =======


    str_read = ser.readline()

    input1 = str_read
    
    str_comp = "RECEIVED OFF"
       
    newString = convertString(str_read)
    input1 = newString
    
##========================= SOUND BUTTONS ========================      
        
    if(newString == str_comp):
        print("DREAMS DO COME TRUE")
        
    if(puzzle == "stand1"):
            
        if ( newString == "SOUND_1"):
            print("THUNDER")
            soundChannelA.play(sndA) 
        if ( newString == "SOUND_2"):
            print("WAVE")
            soundChannelA.play(sndB)
        if ( newString == "SOUND_3"):
            print("SHEEP")
            soundChannelA.play(sndC)        
        if ( newString == "SOUND_4"):
            print("TRAIN")
            soundChannelA.play(sndD)
        if ( newString == "SOUND_5"):
            print("SAW")
            soundChannelA.play(sndE)
            
    elif(puzzle == "stand2"):
            
            
        if ( newString == "SOUND_1"):
            print("TRACTOR")
            soundChannelA.play(sndA) 
        if ( newString == "SOUND_2"):
            print("LIGH RAIN")
            soundChannelA.play(sndB)
        if ( newString == "SOUND_3"):
            print("HORN")
            soundChannelA.play(sndC)        
        if ( newString == "SOUND_4"):
            print("HEART")
            soundChannelA.play(sndD)
        if ( newString == "SOUND_5"):
            print("JET")
            soundChannelA.play(sndE) 
#========================= SOUND CARD STAND # 1 ========================        
# ------ SOUND CARD # 1-------------------------
    if(puzzle == "stand1"):

        if(newString == "1_INSERTED"):
            #print("CARD 1 IN")
            client.publish("phone/box1/sc1", 1)
        elif(newString == "1_REMOVED"):
            #print("CARD 1 OUT")
            client.publish("phone/box1/sc1", 0)
            
    # ------ SOUND CARD # 2-------------------------
        elif(newString == "2_INSERTED"):
            client.publish("phone/box1/sc2", 1)
        elif(newString == "2_REMOVED"):
            client.publish("phone/box1/sc2", 0)
            
    # ------ SOUND CARD # 3-------------------------
        elif(newString == "3_INSERTED"):
            client.publish("phone/box1/sc3", 1)
        elif(newString == "3_REMOVED"):
            client.publish("phone/box1/sc3", 0)   

    # ------ SOUND CARD # 4-------------------------
        elif(newString == "4_INSERTED"):
            client.publish("phone/box1/sc4", 1)
        elif(newString == "4_REMOVED"):
            client.publish("phone/box1/sc4", 0)
        
    # ------ SOUND CARD # 5-------------------------
        elif(newString == "5_INSERTED"):
            client.publish("phone/box1/sc5", 1)
        elif(newString == "5_REMOVED"):
            client.publish("phone/box1/sc5", 0)

    # ------ PUZZLE STATUS-------------------------
        elif(newString == "SC_1_SOLVED"):
            client.publish("phone/box1/status",1)
            print("pi SOLVED")
        elif(newString == "SC_1_RESET"):
            client.publish("phone/box1/status", 0)
            print("pi RESET")
            
        elif(newString == "redPress"):
            client.publish("phone/box1/red",1)

        elif(newString == "redReset"):
            client.publish("phone/box1/red", 0)


#========================= SOUND CARD STAND # 2 ========================
    elif (puzzle == "stand2"):
    # ------ SOUND CARD # 1-------------------------
        if(newString == "1_INSERTED"):
            #print("CARD 1 IN")
            client.publish("phone/box2/sc1", 1)
        elif(newString == "1_REMOVED"):
            #print("CARD 1 OUT")
            client.publish("phone/box2/sc1", 0)
            
    # ------ SOUND CARD # 2-------------------------
        elif(newString == "2_INSERTED"):
            client.publish("phone/box2/sc2", 1)
        elif(newString == "2_REMOVED"):
            client.publish("phone/box2/sc2", 0)
            
    # ------ SOUND CARD # 3-------------------------
        elif(newString == "3_INSERTED"):
            client.publish("phone/box2/sc3", 1)
        elif(newString == "3_REMOVED"):
            client.publish("phone/box2/sc3", 0)   

    # ------ SOUND CARD # 4-------------------------
        elif(newString == "4_INSERTED"):
            client.publish("phone/box2/sc4", 1)
        elif(newString == "4_REMOVED"):
            client.publish("phone/box2/sc4", 0)
        
    # ------ SOUND CARD # 5-------------------------
        elif(newString == "5_INSERTED"):
            client.publish("phone/box2/sc5", 1)
        elif(newString == "5_REMOVED"):
            client.publish("phone/box2/sc5", 0)

    # ------ PUZZLE STATUS-------------------------
        elif(newString == "SC_1_SOLVED"):
            client.publish("phone/box2/status", 1)
            print("pi SOLVED")
        elif(newString == "SC_1_RESET"):
            client.publish("phone/box2/status", 0)
            print("pi RESET")
            
                    
        elif(newString == "redPress"):
            client.publish("phone/box2/red",1)

        elif(newString == "redReset"):
            client.publish("phone/box2/red", 0)
            
        time.sleep(0.1)
#        print('Button Pressed : ')

    #songP = True
    
    #ser.write('5'.encode())

# Kill Music Command
#subprocess.call(['killall','mpg123'])

#Play Command
#subprocess.Popen(['mpg123', mp3_files[index]])
#subprocess.Popen(['mpg123', EyeOfTheTiger.mp3])

    

