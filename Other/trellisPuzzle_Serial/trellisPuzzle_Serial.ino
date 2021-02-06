



// DATE CREATED: 12/6/18
// LAST DATE EDITED: 12/7/18

// PROJECT: Trellis Matices

// PROJECT: Trellis Matices
// CURRENT STATUS/BUGS: 
// NOTES: TESTED AND WORKING!!!!!
//  


/*************************************************** 
  This is a test example for the Adafruit Trellis w/HT16K33

  Designed specifically to work with the Adafruit Trellis 
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"

/*************************************************** 
  This example shows reading buttons and setting/clearing buttons in a loop
  "momentary" mode has the LED light up only when a button is pressed
  "latching" mode lets you turn the LED on/off when pressed

  Up to 8 matrices can be used but this example will show 4 or 1
 ****************************************************/

//----------- DEFINES -------------------------------------------------------------
//#define DEBUG

#define MAGLOCK 0
#define LEDLIGHT 1
// set the mode here
#define OUTPUTMODE MAGLOCK 

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING 

#define RELAY_PIN1 2
#define RELAY_PIN2 3

//----------- FUNCTIONS -------------------------------------------------------------

void setFlag (int );
void clrFlag (int );

void checkCorrect();
bool checkCorrect_1 ( );
bool checkCorrect_2 ( );

void youWON(int );
void winDisplay(int );

void reset(int );
void checkReset();
void checkReset1(int );
void checkReset2(int );

// not needed ?
void setFlagel(int );
void clearFlagel(int );

bool check1 = false;
bool check2 = false;

void printArray(int []);
void clearArray(int []);

//---- Serial Communication ----
char Comp(char* );


//---- Serial Communication ----
char inData[20];
char inChar=-1;
byte index = 0;
int incoming_state = 0;
char incoming_char = 0;

//----------- VARIABLES -------------------------------------------------------------

bool tellisWON_1 = false;
bool tellisWON_2 = false;

//----------- TRELLIS INFO -------------------------------------------------------------

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();

// uncomment the below to add 3 more matrices

//Adafruit_Trellis matrix2 = Adafruit_Trellis();
//Adafruit_Trellis matrix3 = Adafruit_Trellis();
// you can add another 4, up to 8

// Just one
//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1);
// or use the below to select 4, up to 8 can be passed in
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1);
//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 2

#define numKeys (NUMTRELLIS * 16)
//#define maxCorrect 4
#define trellisKeys 16

// Connect Trellis Vin to 5V and Ground to ground.
// Connect the INT wire to pin #A2 (can change later!)
#define INTPIN A2
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin! 
// Even 8 tiles use only 3 wires max



bool fakeReset_R = false;
bool fakeWin_R = false;

bool fakeReset_B = false;
bool fakeWin_B = false;

bool firstLoop = true;

int correctKeys[16]={0,1,2,3};
int trellisNum1[16];
int trellisNum2[16]; 

int trellisNum1_Correct[16] = { 1, 1, 1, 1,
                                0, 0, 0, 0, 
                                0, 0, 0, 0,
                                0, 0, 0, 0};
                                
int trellisNum2_Correct[16]  = { 1, 1, 1, 1,
                                 0, 0, 0, 0, 
                                 0, 0, 0, 0,
                                 0, 0, 0, 0};

// RESET CODE: 0,5,10,15                                
int trellisNum1_Reset[16] =    { 1, 0, 0, 0,
                                 0, 1, 0, 0, 
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};
                                
int trellisNum2_Reset[16]  =   { 1, 0, 0, 0,
                                 0, 1, 0, 0, 
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};
int resetArray1[]= {0,5,10,15};
int resetArray2[]= {16,21,26,31};
int currReset1[4];
int currReset2[4];

//=========================== SETUP ==========================================================
void setup() {
  Serial.begin(9600);
  #ifdef DEBUG
  Serial.println(" TRELLIS PUZZLE TEST MODE");
  Serial.println(" -------------------------");
  #endif

  if(firstLoop){
    delay(500);
    Serial.println("RED_RESET");
    delay(1000);
    Serial.println("BLUE_RESET");
  }
  
//----------- PIN MODES -------------------------------------------------------------

  //---------------RELAY--------------- 
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  
 if (OUTPUTMODE == MAGLOCK){
  digitalWrite(RELAY_PIN1, HIGH);  
  digitalWrite(RELAY_PIN2, HIGH);
 }
 if (OUTPUTMODE == LEDLIGHT){
  digitalWrite(RELAY_PIN1, LOW);  
  digitalWrite(RELAY_PIN2, LOW);
 }
  
  //---------------INPUT PIN---------------  
  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  
  // begin() with the addresses of each panel in order
  // I find it easiest if the addresses are in order
  trellis.begin(0x70, 0x71);  // only one
  //trellis.begin(0x70, 0x71, 0x72, 0x73);  // or four!

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  
  for( int i = 0 ; i < trellisKeys ; i++){
    trellisNum1[i] = 0;
    trellisNum2[i] = 0;    
  } 
}

//=========================== LOOP ==========================================================
void loop() {
  delay(30); // 30ms delay is required, dont remove me!

  if (Comp ("blueSOLVED") == 0){
    fakeWin_B = true;
    youWON(1);

  }
  else if (Comp ("blueRESET") == 0){
    fakeReset_B = true;
    reset(1);

  }
  else if (Comp ("redSOLVED") == 0){
    fakeWin_R = true;
    youWON(2);

  }  
  else if (Comp ("redRESET") == 0){
    fakeReset_R = true;
    reset(2);
  }
  else{
    //NULL
  }

  
  if (MODE == MOMENTARY) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i=0; i<numKeys; i++) {
	// if it was pressed, turn it on
	if (trellis.justPressed(i)) {
	  //Serial.print("v"); Serial.println(i);

	  trellis.setLED(i);
	} 
	// if it was released, turn it off
	if (trellis.justReleased(i)) {
	  //Serial.print("^"); Serial.println(i);
   
	  trellis.clrLED(i);
	}
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }

// ========================= START OF CODE FOR LATCHING =========================

  if (MODE == LATCHING) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i=0; i<numKeys; i++) {
        
        bool trellnum1 = false;
        if(i<16){
          trellnum1=true;
        }
        // if it was pressed...
	if (trellis.justPressed(i)) {
  #ifdef DEBUG
	  Serial.print("v"); Serial.println(i);
  #endif
	  // Alternate the LED
	  if (trellis.isLED(i)){
      // only change LED states of a Trellis is the Puzzle hasn't been won
      // but still keep track of button presses for RESET
      
      if(trellnum1){ // Key pressed on Trellis #1
        if(!tellisWON_1){ // if Trellis #1 isn't WON display LED
          trellis.clrLED(i);          
        }
      }
      else{ // Key pressed on Trellis #2
        if(!tellisWON_2){ // if Trellis #2 isn't WON display LED
          trellis.clrLED(i);          
        }
      }
	    //trellis.clrLED(i);      
      clrFlag(i);
	  }
	  else{
      if(trellnum1){ // Key pressed on Trellis #1
        if(!tellisWON_1){ // if Trellis #1 isn't WON display LED
          trellis.setLED(i);        
        }
      }
      else{ // Key pressed on Trellis #2
        if(!tellisWON_2){ // if Trellis #2 isn't WON display LED
          trellis.setLED(i);         
        }
      }
	   // trellis.setLED(i);
      
      setFlag(i);
	  }
// A KEY HAS BEEN PRESSED - END OF LOOP
      if(trellnum1){ // Key pressed on Trellis #1
        if(tellisWON_1){ // if Trellis #1 is't WON display LED
          checkReset1(i);      
        }
      }
      else{ // Key pressed on Trellis #2
        if(tellisWON_2){ // if Trellis #2 is't WON display LED
          checkReset2(i);           
        }
      }
      
        } 
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
      
      checkCorrect();

      }
    }
// ========================= END OF CODE FOR LATCHING =========================
  
}


//========================================== FUNCTIONS ===================================================================

//----------- YOU WON THE GAME - SEQUENCE -----------------------------------------------
void youWON(int trellNum){
#ifdef DEBUG
Serial.println("YOU WON");
#endif

  if (trellNum == 1){
    tellisWON_1 = true;
    // Winning Sequence for Matrix #1
     if (MODE == MAGLOCK){
      digitalWrite(RELAY_PIN1, LOW);  
     }
     if (MODE == LEDLIGHT){
      digitalWrite(RELAY_PIN1, HIGH);  
     }
     //clearArray(trellisNum1); 
     winDisplay(1); 
  }

  else if (trellNum == 2){
    tellisWON_2 = true;
    // Winning Sequence for Matrix #2
    if (MODE == MAGLOCK){
      digitalWrite(RELAY_PIN2, LOW);  
     }
     if (MODE == LEDLIGHT){
      digitalWrite(RELAY_PIN2, HIGH);  
     }
    //clearArray(trellisNum2);  
    winDisplay(2); 
  }
  
}

//----------- RESET SEQUENCE -----------------------------------------------
void reset(int tempTrell){
#ifdef DEBUG
Serial.println("RESET TRELLIS: ");
Serial.print(tempTrell);
Serial.println();
#endif

// ----- RESET TRELLIS #1 ----- 
  if(tempTrell == 1){
    if(!fakeReset_B) Serial.println("blueRESET");
    clearArray(trellisNum1); 
    tellisWON_1 = false;
    fakeWin_B = false;
    fakeReset_B = false;
     if (MODE == MAGLOCK){
      digitalWrite(RELAY_PIN1, HIGH);
     }
     if (MODE == LEDLIGHT){
      digitalWrite(RELAY_PIN1, LOW);  
     }
  }

// ----- RESET TRELLIS #1 ----- 
  else if (tempTrell == 2 ){
    if(!fakeReset_R) Serial.println("redRESET");
    clearArray(trellisNum2);
    tellisWON_2 = false;
    fakeWin_R = false;
    fakeReset_R = false;
     if (MODE == MAGLOCK){
      digitalWrite(RELAY_PIN2, HIGH);  
     }
     if (MODE == LEDLIGHT){
      digitalWrite(RELAY_PIN2, LOW);  
     }
  }
}

//----------- CHECK FOR RESET - Trellis # 1 -----------------------------------------------
void checkReset1(int trellKey){
// after game is WON check Trellis #1 for the sequence of buttons
// RETURN FALSE: if reset Array is wrong
// RETURN TRUE: if Reset Sequence is correct

  currReset1[0] = currReset1[1];
  currReset1[1] = currReset1[2];
  currReset1[2] = currReset1[3];
  currReset1[3] = trellKey;
  
// RESET CODE: 0,5,10,15 
  for(int i=0 ; i<4 ; i++){
    if( currReset1[i] != resetArray1[i]){
      return ;
    }
  }
  reset(1);
  //return true;

}

//----------- CHECK FOR RESET - Trellis # 2 -----------------------------------------------
void checkReset2(int trellKey){
// after game is WON check Trellis #2 for the sequence of buttons
// RETURN FALSE: if reset Array is wrong
// RETURN TRUE: if Reset Sequence is correct

  currReset2[0] = currReset2[1];
  currReset2[1] = currReset2[2];
  currReset2[2] = currReset2[3];
  currReset2[3] = trellKey;
  
// RESET CODE: 0,5,10,15 
  for(int i=0 ; i<4 ; i++){
    if( currReset2[i] != resetArray2[i]){
      return ;
    }
  }
  reset(2);
  //return true;

}

//----------- CHECK FOR RESET - Trellis # 1 -----------------------------------------------
void checkReset(){
  // all reset key have to be pressed (on both Trellis) for a game reset
  // and at least 1 Trellis has to be won
  // RESET: if all Matrix keys are correct -> trellisNum1_Reset , trellisNum2_Reset
  // RETURN : if any Matrix key are incorrect

// CHECK TRELLIS 1 FOR RESET
  for( int i=0 ; i < trellisKeys ; i++){
    if( trellisNum1[i] != trellisNum1_Reset[i]){
      //return false if any key is incorrect
      return;
    }
    else{
      // nothing else
    }
  }
// ----- AT THIS POINT TRELLIS 1 RESET IS CODE IS CORRECT -----

// CHECK TRELLIS 2 FOR RESET
  for( int i=0 ; i < trellisKeys ; i++){
    if( trellisNum2[i] != trellisNum2_Reset[i]){
      //return if any key is incorrect
      return;
    }
    else{
      // nothing else
    }
  }

// if no keys are incorrect on either Trellis 1 or 2 -> RESET GAME
  //reset();
}

//----------- SET MATRIX FLAGS FOR BUTTON PRESS -----------------------------------------------
// sets flags for button presses - this is where MOD (%) is used to change MATRIX #2 inputs
void setFlag (int keyNum){
#ifdef DEBUG
Serial.println("Set Flag");
#endif

// Set Flag for Trellis #1 - Key Pressed
  if(keyNum<16){
    trellisNum1[keyNum]=1;
    #ifdef DEBUG
    Serial.println("set flag Trellis #1");
    Serial.println(keyNum);
    #endif
  }

// Set Flag for Trellis #2 - Key Pressed
  else if(keyNum >= 16 && keyNum <=31){
    int modKey = 0;
    modKey = keyNum%16;
    trellisNum2[modKey]=1;
  }
}

//----------- CLEAR MATRIX FLAGS FOR BUTTON RELEASE -----------------------------------------------
void clrFlag (int keyNum){
#ifdef DEBUG
Serial.println("Clear Flag");
#endif

// Set Flag for Trellis #1 - Key Pressed
  if(keyNum<16){
    trellisNum1[keyNum]=0;
  }

// Set Flag for Trellis #2 - Key Pressed
  else if(keyNum >= 16 && keyNum <=31){
    int modKey = 0;
    modKey = keyNum%16;
    trellisNum2[modKey]=0;
  }
}

//----------- CHECK IF MATRIXS 1 & 2 ARE CORRECT -----------------------------------------------
void checkCorrect(){
  // checks if either Trellis is Correct for WIN -> if so -> youWON()

//only check if Trellis is correct it hasn't been WON yet

  if(!tellisWON_1){
    check1 = checkCorrect_1();   
    if(check1){
      youWON(1);
   } 
  }
  
  if(!tellisWON_2){
    check2 = checkCorrect_2();    
    if(check1){
      youWON(1);
   } 
  }
}

//----------- CHECK MATRIX # 1 CORRECT -----------------------------------------------
bool checkCorrect_1 (){
  // RETURN TRUE: if all Matrix keys are correct
  // RETURN FALSE: if any Matrix key are incorrect
  
  for( int i=0 ; i < trellisKeys ; i++){
    if( trellisNum1[i] != trellisNum1_Correct[i]){
      //Serial.println("FALSE");
     // printArray(trellisNum1);
      return false;
    }
    else{
     // Serial.println();
      //Serial.print("Correct Button: ");
      //Serial.print(i);
      //Serial.println();
    }
  }
  #ifdef DEBUG
  Serial.println("Returning True - Trellis 1");
  #endif
  
  return true;
}

//----------- CHECK MATRIX # 2 CORRECT -----------------------------------------------
bool checkCorrect_2 (){
  // RETURN TRUE: if all Matrix keys are correct
  // RETURN FALSE: if any Matrix key are incorrect

  for( int i=0 ; i < trellisKeys ; i++){
    if( trellisNum2[i] != trellisNum2_Correct[i]){
      //printArray(trellisNum2);
      return false;
    }
  }
  #ifdef DEBUG
  Serial.println("Returning True - Trellis 2");
  #endif

  return true;
}

//----------- DISPLAY WIN -> LEDS -----------------------------------------------

void winDisplay(int trellNum){
#ifdef DEBUG
  Serial.println("Win Display");
  Serial.println(trellNum);
#endif

  if (trellNum == 1){
    if(!fakeWin_B) Serial.println("blueSOLVED");

  // clear all LEDs
  for (uint8_t i=0; i<trellisKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
  }
  delay(50);

  // turn them on
  for (uint8_t i=0; i<trellisKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<trellisKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }

  // Display Winning Buttons

    clearArray(trellisNum1);
  
  }

  else if (trellNum == 2){
    if(!fakeWin_R) Serial.println("redSOLVED");

  // then turn them off
  for (uint8_t i=trellisKeys; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
        
  for (uint8_t i=trellisKeys; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=trellisKeys; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }

    clearArray(trellisNum2);
  
  }
  
}

//----------- PRINT ARRAY -----------------------------------------------
void printArray(int tempArray[]){
  
    Serial.println();
    Serial.print("Trellis Array #1: ");
  
  for( int i = 0 ; i < trellisKeys ; i++){
    Serial.print(trellisNum1[i]);
    Serial.print(" , ");  
  }

   Serial.println();
   Serial.print("Trellis Array #2: ");
  
  for( int i = 0 ; i < trellisKeys ; i++){
    Serial.print(trellisNum2[i]);
    Serial.print(" , ");  
  }


  
  Serial.println();
}

//----------- CLEAR ARRAY -----------------------------------------------
void clearArray(int tempArray[]){
    for( int i = 0 ; i < trellisKeys ; i++){
    tempArray[i] = 0;
    //trellisNum2[i] = 0;    
  }
  
}











void setFlagel(int keyNum){
  switch(keyNum){

    case 0: // code to be executed if n = 1;
        break;
    case 1: // code to be executed if n = 1;
        break;
    case 2: // code to be executed if n = 2;
        break;
    case 3: // code to be executed if n = 1;
        break;
    case 4: // code to be executed if n = 2;
        break;
    case 5: // code to be executed if n = 1;
        break;
    case 6: // code to be executed if n = 2;
        break;
    case 7: // code to be executed if n = 1;
        break;
    case 8: // code to be executed if n = 2;
        break;
    case 9: // code to be executed if n = 1;
        break;
    case 10: // code to be executed if n = 2;
        break;
    case 11: // code to be executed if n = 1;
        break;
    case 12: // code to be executed if n = 2;
        break;
    case 13: // code to be executed if n = 1;
        break;
    case 14: // code to be executed if n = 2;
        break;
    case 15: // code to be executed if n = 1;
        break;
    case 16: // code to be executed if n = 2;
        break;
        


    case 17: // code to be executed if n = 1;
        break;
    case 18: // code to be executed if n = 2;
        break;
    case 19: // code to be executed if n = 1;
        break;
    case 20: // code to be executed if n = 2;
        break;
    case 21: // code to be executed if n = 1;
        break;
    case 22: // code to be executed if n = 2;
        break;
    case 23: // code to be executed if n = 1;
        break;
    case 24: // code to be executed if n = 2;
        break;
    case 25: // code to be executed if n = 1;
        break;
    case 26: // code to be executed if n = 2;
        break;
    case 27: // code to be executed if n = 1;
        break;
    case 28: // code to be executed if n = 2;
        break;
    case 29: // code to be executed if n = 1;
        break;
    case 30: // code to be executed if n = 2;
        break;
    case 31: // code to be executed if n = 1;
        break;
    case 32: // code to be executed if n = 2;
        break;



        
    default: // code to be executed if n doesn't match any cases
        break;
    
  }
}

void clearFlagel (int keyNum){
  
  switch(keyNum){

    case 0: // code to be executed if n = 1;
        break;
    case 1: // code to be executed if n = 1;
        break;
    case 2: // code to be executed if n = 2;
        break;
    case 3: // code to be executed if n = 1;
        break;
    case 4: // code to be executed if n = 2;
        break;
    case 5: // code to be executed if n = 1;
        break;
    case 6: // code to be executed if n = 2;
        break;
    case 7: // code to be executed if n = 1;
        break;
    case 8: // code to be executed if n = 2;
        break;
    case 9: // code to be executed if n = 1;
        break;
    case 10: // code to be executed if n = 2;
        break;
    case 11: // code to be executed if n = 1;
        break;
    case 12: // code to be executed if n = 2;
        break;
    case 13: // code to be executed if n = 1;
        break;
    case 14: // code to be executed if n = 2;
        break;
    case 15: // code to be executed if n = 1;
        break;
    case 16: // code to be executed if n = 2;
        break;
        


    case 17: // code to be executed if n = 1;
        break;
    case 18: // code to be executed if n = 2;
        break;
    case 19: // code to be executed if n = 1;
        break;
    case 20: // code to be executed if n = 2;
        break;
    case 21: // code to be executed if n = 1;
        break;
    case 22: // code to be executed if n = 2;
        break;
    case 23: // code to be executed if n = 1;
        break;
    case 24: // code to be executed if n = 2;
        break;
    case 25: // code to be executed if n = 1;
        break;
    case 26: // code to be executed if n = 2;
        break;
    case 27: // code to be executed if n = 1;
        break;
    case 28: // code to be executed if n = 2;
        break;
    case 29: // code to be executed if n = 1;
        break;
    case 30: // code to be executed if n = 2;
        break;
    case 31: // code to be executed if n = 1;
        break;
    case 32: // code to be executed if n = 2;
        break;



        
    default: // code to be executed if n doesn't match any cases
        break;
    
  }
}

//----------- COMPARE INCOMING STRING FROM SERIAL -----------------------------------------------
char Comp(char* This){
  while(Serial.available() > 0)
  {
    if(index < 19)
    {
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
      inData[index] = '\0';
    }
  }

  if (strcmp(inData,This) == 0){
    for ( int i=0 ; i<19 ; i++){
      inData[i] = 0;
    }
    index=0;
    return(0);
  }
  else{
    return(1);
  }
}
