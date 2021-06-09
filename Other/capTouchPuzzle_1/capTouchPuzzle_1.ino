// BELIEVED TO BE THE LATEST TOUCH SENSOR PUZZLE
// CAP TOUCH 12 CHANNEL 


// last date edited 3/7/2020

/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int capState1 = 0, capState2 =0, capState3 = 0, capState4 =0, capState5 = 0, capState6 =0, capState7 = 0, capState8 =0, capState9 = 0;
int ledCount = 0;
int badSquare =0;

int ledFlag2 = 0;
int ledFlag3 = 0;
int ledFlag5 = 0;
int ledFlag7 = 0;
int ledFlag9 = 0;

int relayPin = 7;


  int dBdelay=50;

 //setThreshholds(5, 5);


void setup() {

  pinMode(6,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);

  digitalWrite(6,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(7,HIGH);

  

 
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

//  setThreshholds(uint8_t touch, uint8_t release);
}

void loop() {

  
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      delay(dBdelay);
      
      if(cap.touched()==currtouched){
         switch(i){
        case 1: capState1=1;
          ledFlag2 = 0;
          ledFlag3 = 0;
          ledFlag5 = 0;
          ledFlag7 = 0;
          ledFlag9 = 0;
          break;
        case 2: capState2=1;
          ledFlag2 = 1;
          break;
        case 3: capState3=1;
          ledFlag3 = 1;
          break;
        case 4: capState4=1;
          ledFlag2 = 0;
          ledFlag3 = 0;
          ledFlag5 = 0;
          ledFlag7 = 0;
          ledFlag9 = 0;
          break;
        case 5: capState5=1;
          ledFlag5 = 1;
          break;
        case 6: capState6=1;
          ledFlag2 = 0;
          ledFlag3 = 0;
          ledFlag5 = 0;
          ledFlag7 = 0;
          ledFlag9 = 0;
          break;
        case 7: capState7=1;
          ledFlag7 = 1;
          break;
        case 8: capState8=1;
          ledFlag2 = 0;
          ledFlag3 = 0;
          ledFlag5 = 0;
          ledFlag7 = 0;
          ledFlag9 = 0;
          break;
        case 9: capState9=1;
          ledFlag9 = 1;
          break;
      }
        
      }

      
     

      // CHECK ALL CAPSTATES ===========
//      if (capState2 == 1) ledCount = ledCount + 1;
//      if (capState3 == 1) ledCount = ledCount + 1;
//      if (capState5 == 1) ledCount = ledCount + 1;
//      if (capState7 == 1) ledCount = ledCount + 1;
//      if (capState9 == 1) ledCount = ledCount + 1;
//
//      
//      if (capState1 == 1){
//        ledCount = 0;
//        capState1 = 0;
//      }
//      if (capState4 == 1){
//        ledCount = 0;
//        capState2 = 0;
//      }
//      if (capState6 == 1){
//        ledCount = 0;
//        capState6 = 0;
//      }
//      if (capState8 == 1){
//        ledCount = 0;
//        capState8 = 0;
//      }

      //UPDATE LEDs ===================

      ledCount = ledFlag2 + ledFlag3 + ledFlag5 + ledFlag7 + ledFlag9;

      switch(ledCount){
         case 0: digitalWrite(6,LOW);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          break;
        case 1: digitalWrite( 6 , HIGH);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          break;
        case 2: digitalWrite( 6 , HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          break;
        case 3: digitalWrite( 6 , HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          break;
        case 4: digitalWrite( 6 , HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,LOW);
          break;
        case 5: digitalWrite( 6 , HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite( 5 , HIGH);
          delay(100);

          digitalWrite(relayPin,LOW);
          //WINNING SEQUENCE =============
          digitalWrite(6,LOW);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          delay(100);

          digitalWrite(6,HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          delay(100);

          digitalWrite(6,LOW);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          delay(100);

          digitalWrite(6,HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          delay(100);

          digitalWrite(6,LOW);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          delay(100);

          digitalWrite(6,HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          delay(100);

          digitalWrite(6,LOW);
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          delay(100);

          ledCount =0;
          //break;

          capState1=0;
          capState2=0;
          capState3=0;
          capState4=0;
          capState5=0;
          capState6=0;
          capState7=0;
          capState8=0;
          capState9=0;

          ledFlag2 = 0;
          ledFlag3 = 0;
          ledFlag5 = 0;
          ledFlag7 = 0;
          ledFlag9 = 0;

          digitalWrite(relayPin,HIGH);

          break;
          default:
          break;

          

      }
//      
//      
//      if(i==1){
//        digitalWrite( 6, HIGH);
//      }
//      if(i==2){
//        digitalWrite( 2, HIGH);
//      }
//      if(i==3){
//        digitalWrite( 3, HIGH);
//      }
//      if(i==4){
//        digitalWrite( 4, HIGH);
//      }
//      if(i==5){
//        digitalWrite( 5, HIGH);
//      }
//      if(i==6){
//        digitalWrite(6,LOW);
//        digitalWrite(2,LOW);
//        digitalWrite(3,LOW);
//        digitalWrite(4,LOW);
//        digitalWrite(5,LOW);
//        
//      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
