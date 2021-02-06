// PUZZLE : CIRCLE PUZZL3
// NOTES : SHES A BEAUT!
// Last Edited: 1/29/18

// working with MQTT!!

// SHES A BEAUTY

// PREVIOUS CODE: SEQUENCE PUZZLE
// NOTES: 
// --   TESTING AND WORKING
// --   Modify MODE - depending on LED or MAGLOCK

// --   FOR IN GAME USE
//      -->  comment out DEBUG
//      -->  comment out TESTING
//      -->  STATUS GAMEPLAY

/*
 CIRCLE #1 : 1 , 4 , 8 , 9 , 6 , 2
 CIRCLE #2 : 2 , 5 , 9 , 10 , 7 , 3
 CIRCLE #3 : 5 , 8 , 11 , 12 , 10 , 6
 WINNING   : 2 , 5 , 6 , 8 , 9 , 10
 START     : 2 , 4 , 7 , 8 , 10 , 11
*/

//----------- DEFINES -------------------------------------------------------------

// ***************** SEQ CODE - START *******************************************************************

#define MAGLOCK_s 1
#define LEDLIGHT_s 0
// set the mode here
#define OUTPUT_MODE MAGLOCK_s 

#define numButtons_s 7
#define numLEDS_s 7

#define RELAY_PIN_s 6

//#define ButtonPin_1_s 35
//#define ButtonPin_2_s 33
//#define ButtonPin_3_s 31
//#define ButtonPin_4_s 29
//#define ButtonPin_5_s 27
//#define ButtonPin_6_s 25
//#define ButtonPin_7_s 23

#define ButtonPin_1_s 34
#define ButtonPin_2_s 32
#define ButtonPin_3_s 30
#define ButtonPin_4_s 28
#define ButtonPin_5_s 26
#define ButtonPin_6_s 24
#define ButtonPin_7_s 22


/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
#define ButtonPin_8 8
#define ButtonPin_9 9
#define ButtonPin_1_s0 10
*/


#define LEDPIN_1_s 35
#define LEDPIN_2_s 33
#define LEDPIN_3_s 31
#define LEDPIN_4_s 29
#define LEDPIN_5_s 27
#define LEDPIN_6_s 25
#define LEDPIN_7_s 23

//#define LEDPIN_1_s 34
//#define LEDPIN_2_s 32
//#define LEDPIN_3_s 30
//#define LEDPIN_4_s 28
//#define LEDPIN_5_s 26
//#define LEDPIN_6_s 24
//#define LEDPIN_7_s 22

static int state_s=0;
static int reset_sstate_s = 0;
const int winDelay_s = 100;
bool gameWON_s = false;


//----------- FUNCTIONS -------------------------------------------------------------

void ledsON_s_s();
void ledsOFF_s();
void flashLEDS_s(int  , int );

void getInput_s(int );  // Gets user inputs

void checkstate_s();
void youWON_s(); // What happens when you winner!!
void reset_s();


//----------- VARIABLES -------------------------------------------------------------

//---- Serial Communication ----
char inData_s[20];
char inChar_s=-1;
byte index_s = 0;
int incoming_state_s = 0;
char incoming_char_s = 0;


int lightDelay_s = 200; // delay to leave LED light on before checking state_s

//bool gameWON_s = false;

unsigned long debounceDelay_s = 50; // Increase is there is to much noise
unsigned long lastDebounceTime_s = 0;

int bufferVal_s[numButtons_s];
int buttonstate_s[numButtons_s];
int laststate_s[numButtons_s];

// ***************** SEQ CODE - END *********************************************************************

//#define DEBUG
#define TESTING

#define LEDTEST 0
#define GAMEPLAY 1
// set the mode here
#define STATUS GAMEPLAY 

#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 


#define numButtons 4
#define numLEDS 12

#define RELAY_PIN 7

#define ButtonPin_1 42
#define ButtonPin_2 44
#define ButtonPin_3 46
#define ResetButtonPin 48


/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
#define ButtonPin_5 5
#define ButtonPin_6 6
#define ButtonPin_7 7
*/


//#define LEDPIN_1 53
//#define LEDPIN_2 51
//#define LEDPIN_3 49
//#define LEDPIN_4 47
//#define LEDPIN_5 45
//#define LEDPIN_6 43
//#define LEDPIN_7 41
//#define LEDPIN_8 39
//#define LEDPIN_9 37
//#define LEDPIN_10 35
//#define LEDPIN_11 33
//#define LEDPIN_12 31

#define LEDPIN_1 37
#define LEDPIN_2 39
#define LEDPIN_3 41
#define LEDPIN_4 43
#define LEDPIN_5 45
#define LEDPIN_6 47
#define LEDPIN_7 49
#define LEDPIN_8 51
#define LEDPIN_9 53
#define LEDPIN_10 36
#define LEDPIN_11 38
#define LEDPIN_12 40


//----------- FUNCTIONS -------------------------------------------------------------

//---- Serial Communication ----
char Comp_s(char* );


void ledsON();
void ledsOFF();
void flashLEDS(int  , int );

void getInput(int );  // Gets user inputs
void checkWin();
void updateLEDS();
void oneLED(int );
void setWin();

void youWIN(); // What happens when you winner!!
void reset();

int buttonCycle = 0;




// ---------- STARTING STATE OF LEDS ----------
const bool _ledFlag1 = false;
const bool _ledFlag2 = true;
const bool _ledFlag3 = false;
const bool _ledFlag4 = true;
const bool _ledFlag5 = false;
const bool _ledFlag6 = false;
const bool _ledFlag7 = true;
const bool _ledFlag8 = true;
const bool _ledFlag9 = false;
const bool _ledFlag10 = true;
const bool _ledFlag11 = true;
const bool _ledFlag12 = false;

// ---------- WINNING STATE OF LEDS ----------
const bool win_ledFlag1 = false;
const bool win_ledFlag2 = true;
const bool win_ledFlag3 = false;
const bool win_ledFlag4 = false;
const bool win_ledFlag5 = true;
const bool win_ledFlag6 = true;
const bool win_ledFlag7 = false;
const bool win_ledFlag8 = true;
const bool win_ledFlag9 = true;
const bool win_ledFlag10 = true;
const bool win_ledFlag11 = false;
const bool win_ledFlag12 = false;


// ---------- VARIABLES TO KEEP TRACK OF STATE ----------
bool ledFlag1 = false;
bool ledFlag2 = false;
bool ledFlag3 = false;
bool ledFlag4 = false;
bool ledFlag5 = false;
bool ledFlag6 = false;
bool ledFlag7 = false;
bool ledFlag8 = false;
bool ledFlag9 = false;
bool ledFlag10 = false;
bool ledFlag11 = false;
bool ledFlag12 = false;


static int state=0;
const int winDelay = 200;
bool gameWON = false;



//----------- VARIABLES -------------------------------------------------------------

//---- Serial Communication ----
char inData[20];
char inChar=-1;
byte index = 0;
int incoming_state = 0;
char incoming_char = 0;

unsigned long debounceDelay = 50; // Increase is there is to much noise
unsigned long lastDebounceTime = 0;

int bufferVal[numButtons];
int buttonState[numButtons];
int lastState[numButtons];


//=========================== SETUP ==========================================================
void setup() {

  Serial.begin(9600);
  #ifdef DEBUG
  Serial.println(" CIRCLE PUZZLE TEST MODE");
  Serial.println(" -------------------------");
  #endif
  
  
// ***************** SEQ CODE - START *******************************************************************

//----------- PIN MODES -------------------------------------------------------------

  //---------------RELAY--------------- 
  pinMode(RELAY_PIN_s, OUTPUT);
  
 if (OUTPUT_MODE == MAGLOCK_s){
  digitalWrite(RELAY_PIN_s, HIGH);  
 }
 if (OUTPUT_MODE == LEDLIGHT_s){
  digitalWrite(RELAY_PIN_s, LOW);  
 }

  //---------------BUTTONS---------------  
  pinMode(ButtonPin_1_s,INPUT);
  pinMode(ButtonPin_2_s,INPUT);
  pinMode(ButtonPin_3_s,INPUT);
  pinMode(ButtonPin_4_s,INPUT);
  pinMode(ButtonPin_5_s,INPUT);
  pinMode(ButtonPin_6_s,INPUT);
  pinMode(ButtonPin_7_s,INPUT);

/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
  pinMode(ButtonPin_8,INPUT);
  pinMode(ButtonPin_9,INPUT);
  pinMode(ButtonPin_1_s0,INPUT);
*/

  //---------------LEDS---------------
  pinMode (LEDPIN_1_s,OUTPUT);
  pinMode (LEDPIN_2_s,OUTPUT);
  pinMode (LEDPIN_3_s,OUTPUT);
  pinMode (LEDPIN_4_s,OUTPUT);
  pinMode (LEDPIN_5_s,OUTPUT);
  pinMode (LEDPIN_6_s,OUTPUT);
  pinMode (LEDPIN_7_s,OUTPUT);
  
  //====================================
  
  digitalWrite(LEDPIN_1_s,LOW);
  digitalWrite(LEDPIN_2_s,LOW);
  digitalWrite(LEDPIN_3_s,LOW);
  digitalWrite(LEDPIN_4_s,LOW);
  digitalWrite(LEDPIN_5_s,LOW);
  digitalWrite(LEDPIN_6_s,LOW);
  digitalWrite(LEDPIN_7_s,LOW);


// ***************** SEQ CODE - END *********************************************************************
  
  
  
  
  
  
  ledFlag1 = _ledFlag1;
  ledFlag2 = _ledFlag2;
  ledFlag3 = _ledFlag3;
  ledFlag4 = _ledFlag4;
  ledFlag5 = _ledFlag5;
  ledFlag6 = _ledFlag6;
  ledFlag7 = _ledFlag7;
  ledFlag8 = _ledFlag8;
  ledFlag9 = _ledFlag9;
  ledFlag10 = _ledFlag10;
  ledFlag11 = _ledFlag11;
  ledFlag12 = _ledFlag12;

  

//----------- PIN MODES -------------------------------------------------------------

  //---------------RELAY--------------- 
  pinMode(RELAY_PIN, OUTPUT);

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }

  //---------------BUTTONS---------------  
  pinMode(ButtonPin_1,INPUT);
  pinMode(ButtonPin_2,INPUT);
  pinMode(ButtonPin_3,INPUT);
  pinMode(ResetButtonPin,INPUT);


/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
  pinMode(ButtonPin_5,INPUT);
  pinMode(ButtonPin_6,INPUT);
  pinMode(ButtonPin_7,INPUT);
*/

  //---------------LEDS---------------
  pinMode (LEDPIN_1,OUTPUT);
  pinMode (LEDPIN_2,OUTPUT);
  pinMode (LEDPIN_3,OUTPUT);
  pinMode (LEDPIN_4,OUTPUT);
  pinMode (LEDPIN_5,OUTPUT);
  pinMode (LEDPIN_6,OUTPUT);
  pinMode (LEDPIN_7,OUTPUT);
  pinMode (LEDPIN_8,OUTPUT);
  pinMode (LEDPIN_9,OUTPUT);
  pinMode (LEDPIN_10,OUTPUT);
  pinMode (LEDPIN_11,OUTPUT);
  pinMode (LEDPIN_12,OUTPUT);
  
  //====================================
  
  digitalWrite(LEDPIN_1,_ledFlag1);
  digitalWrite(LEDPIN_2,_ledFlag2);
  digitalWrite(LEDPIN_3,_ledFlag3);
  digitalWrite(LEDPIN_4,_ledFlag4);
  digitalWrite(LEDPIN_5,_ledFlag5);
  digitalWrite(LEDPIN_6,_ledFlag6);
  digitalWrite(LEDPIN_7,_ledFlag7);
  digitalWrite(LEDPIN_8,_ledFlag8);
  digitalWrite(LEDPIN_9,_ledFlag9);
  digitalWrite(LEDPIN_10,_ledFlag10);
  digitalWrite(LEDPIN_11,_ledFlag11);
  digitalWrite(LEDPIN_12,_ledFlag12);

}


//=========================== MAIN LOOP ======================================================
void loop() {

// ***************** SEQ CODE - START *******************************************************************

bufferVal_s[0] = digitalRead(ButtonPin_1_s);
bufferVal_s[1] = digitalRead(ButtonPin_2_s);
bufferVal_s[2] = digitalRead(ButtonPin_3_s);
bufferVal_s[3] = digitalRead(ButtonPin_4_s);
bufferVal_s[4] = digitalRead(ButtonPin_5_s);
bufferVal_s[5] = digitalRead(ButtonPin_6_s);
bufferVal_s[6] = digitalRead(ButtonPin_7_s);
/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
bufferVal_s[7] = digitalRead(ButtonPin_8);
bufferVal_s[8] = digitalRead(ButtonPin_9);
bufferVal_s[9] = digitalRead(ButtonPin_1_s0);
*/
  
  // ---- Serial Communication - Phone Win ----
// received a command from the Pi

if (Comp ("cirSOLVED") == 0){
  if(!gameWON){
    ledFlag2 = win_ledFlag2;
    ledFlag5 = win_ledFlag5;
    ledFlag6 = win_ledFlag6;
    ledFlag8 = win_ledFlag8;
    ledFlag9 = win_ledFlag9;
    ledFlag10 = win_ledFlag10;
  }
  checkWin();
}
else if (Comp ("cirRESET") == 0){
  if(gameWON){
    reset();
    checkWin(); }
}

else if (Comp ("seqSOLVED") == 0){
  //youWON_s();
  getInput_s(7);
  //state_s = 7 ;
  //reset_sstate_s==0;
  //checkstate_s();
  //flashLEDS_s(1,1000);
  
}
else if (Comp ("seqRESET") == 0){
  getInput_s(8);
  //gameWON_s = true;
  //reset_sstate_s = 3;
  //checkstate_s();
  //reset_s();
  //flashLEDS_s(4,100);
}
else{
  //NULL
}
//checkWin
  
  for( int i=0 ; i<numButtons_s ; i++ ){  

    if ( bufferVal_s[i] != laststate_s[i]){ // Switch changed, due to noise or press
      lastDebounceTime_s = millis();
      //Serial.print(" reset_s Debounce Timer ");} // reset_s the debounce timer
    }
      
    if((millis() - lastDebounceTime_s) > debounceDelay_s){ // Change has been longer that debounce delay
      //Serial.print(" Change Long Enough ");
     
      if (bufferVal_s[i] != buttonstate_s[i]){ // If the button state_s changed
        buttonstate_s[i] = bufferVal_s[i]; // Take the bufferVal_s as new state_s
        //Serial.print(" Button state_s is officaially changed ");
        
        if (buttonstate_s[i] == HIGH){ // If  the button is Pressed          
          getInput_s(i);
         //Serial.print("Button Pressed: ");
          //Serial.println(i);
          }
      }
    }
    laststate_s[i] = bufferVal_s[i]; // Save values for next loop
  }



// ***************** SEQ CODE - END *********************************************************************  
  
  
  
  

bufferVal[0] = digitalRead(ButtonPin_1);
bufferVal[1] = digitalRead(ButtonPin_2);
bufferVal[2] = digitalRead(ButtonPin_3);
bufferVal[3] = digitalRead(ResetButtonPin);

/* IF MORE BUTTONS NEEDED UNCOMMENT BELOW 
bufferVal[4] = digitalRead(ButtonPin_5);
bufferVal[5] = digitalRead(ButtonPin_6);
bufferVal[6] = digitalRead(ButtonPin_7);
*/
  
  // ---- Serial Communication - Phone Win ----
// received a command from the Pi

//if (Comp ("cirSOLVED") == 0){
//  if(!gameWON){
//    ledFlag2 = win_ledFlag2;
//    ledFlag5 = win_ledFlag5;
//    ledFlag6 = win_ledFlag6;
//    ledFlag8 = win_ledFlag8;
//    ledFlag9 = win_ledFlag9;
//    ledFlag10 = win_ledFlag10;
//  }
//  checkWin();
//}
//else if (Comp ("cirRESET") == 0){
//  if(gameWON){
//    reset();
//    checkWin(); }
//}
  
  for( int i=0 ; i<numButtons ; i++ ){  

    if ( bufferVal[i] != lastState[i]){ // Switch changed, due to noise or press
      lastDebounceTime = millis();
      //Serial.print(" Reset Debounce Timer ");} // Reset the debounce timer
    }
      
    if((millis() - lastDebounceTime) > debounceDelay){ // Change has been longer that debounce delay
      //Serial.print(" Change Long Enough ");
     
      if (bufferVal[i] != buttonState[i]){ // If the button state changed
        buttonState[i] = bufferVal[i]; // Take the bufferVal as new State
        //Serial.print(" Button State is officaially changed ");
        
        if (buttonState[i] == HIGH){ // If  the button is Pressed          
          getInput(i);
         //Serial.print("Button Pressed: ");
          //Serial.println(i);
          }
         //else // do something maybe
      }
    }
    lastState[i] = bufferVal[i]; // Save values for next loop
  }

// ---------- RESET THE ENTIRE GAME - RELAY INCLUDED ----------
  if(gameWON){
    if(buttonState[0]==HIGH && buttonState[3]==HIGH){
      reset();      
    }
  }

// ---------- CODE ONLY FOR TESTING - BACK DOOR TO WINNING ----------
  #ifdef TESTING
  //if(!gameWON){
    if(buttonState[1]==HIGH && buttonState[2]==HIGH){
      #ifdef DEBUG
      Serial.println("FAKE WIN");
      #endif
      
      setWin();    
      checkWin();
    }
 // }
  #endif


}

// ***************** SEQ CODE - START *******************************************************************

//=========================== FUNCTIONS ======================================================

//----------- Comp_sARE INCOMING STRING FROM SERIAL -----------------------------------------------
char Comp_s(char* This){
  while(Serial.available() > 0)
  {
    if(index_s < 19)
    {
      inChar_s = Serial.read();
      inData_s[index_s] = inChar_s;
      index_s++;
      inData_s[index_s] = '\0';
    }
  }

  if (strcmp(inData_s,This) == 0){
    for ( int i=0 ; i<19 ; i++){
      inData_s[i] = 0;
    }
    index_s=0;
    return(0);
  }
  else{
    return(1);
  }
}

//----------- GET INPUT -----------------------------------------------
void getInput_s(int _input){
#ifdef DEBUG
Serial.println("GOT INPUT");
#endif
  
  switch ( _input){
    case 0: 
      digitalWrite(LEDPIN_1_s,HIGH);
      if( state_s == 0) state_s=1;
      else state_s=0;

      //Serial.println('1');
      break;
      
    case 1: 
      digitalWrite(LEDPIN_2_s,HIGH);
      if( state_s == 1) state_s=2;
      else state_s=0;

      //Serial.println('2');
      break;
      
    case 2:  
      digitalWrite(LEDPIN_3_s,HIGH);
      if( state_s == 2) state_s=3;
      else state_s=0;

      //Serial.println('3');
      break;
      
    case 3: 
      digitalWrite(LEDPIN_4_s,HIGH);
      if( state_s == 3) state_s=4;
      else state_s=0;

      if(gameWON_s){
        if( reset_sstate_s == 1) reset_sstate_s=2;
        else reset_sstate_s=0;
      }
      
      //Serial.println('4');
      break;
      
    case 4:  
      digitalWrite(LEDPIN_5_s,HIGH);
      if( state_s == 4) state_s=5;
      else state_s=0;

      //Serial.println('5');
      break;
      
    case 5: 
      digitalWrite(LEDPIN_6_s,HIGH);
      if( state_s == 5) state_s=6;
      else state_s=0;

      if(gameWON_s){
        if( reset_sstate_s == 0) reset_sstate_s=1;
        else reset_sstate_s=0;
      }

     // Serial.println('6');
      break;
      
    case 6:  
      digitalWrite(LEDPIN_7_s,HIGH);
      if( state_s == 6) state_s=7;
      else state_s=0;

      if(gameWON_s){
        if( reset_sstate_s == 2) reset_sstate_s=3;
        else reset_sstate_s=0;
      }

      //Serial.println('7');
      break;

 //----------------------------------------------
    case 7: 
      //Serial.println('8');
      if(!gameWON_s){
         digitalWrite(LEDPIN_1_s,HIGH);
        state_s=7;
      }
      break;
    case 8: 
      if(gameWON_s) reset_sstate_s=3;
      else reset_sstate_s=0;
      //Serial.println('9');
      break;
    case 9: 
      //Serial.println("10");
      break;
    case 10: 
      //Serial.println("11");
      break;
  
      
    default: // DO NOTHING
      break;
  }
#ifdef DEBUG
Serial.println("CURRENT state_s: ");
Serial.print(state_s);
Serial.println();
#endif

  checkstate_s();
}

//----------- CHECK state_s -----------------------------------------------
// checks state_s for WIN or LEDs OFF
void checkstate_s(){
#ifdef DEBUG
Serial.println("CHECK state_s");
#endif

  delay(lightDelay_s);
  
  if(state_s==0) ledsOFF_s();
  if(state_s==7) youWON_s();

  // check for reset_s SATE
  if(gameWON_s){
    if(reset_sstate_s == 3)
    reset_s();
  }
  
}

//----------- WINNING SEQUENCE -----------------------------------------------
void youWON_s(){
#ifdef DEBUG
Serial.println("WINNING SEQUENCE");
#endif


  delay(winDelay_s);

if(!gameWON_s){
 Serial.println("SEQUENCE_WIN");

 if (OUTPUT_MODE == MAGLOCK_s){
  digitalWrite(RELAY_PIN_s, LOW);  
 }
 if (OUTPUT_MODE == LEDLIGHT_s){
  digitalWrite(RELAY_PIN_s, HIGH);  
 }
  
  flashLEDS_s(4,200);

  gameWON_s = true;
}

else if(gameWON_s){
  //flashLEDS_s(2,100);
}


  //reset_s();
  
}

//----------- reset_s PUZZLE -----------------------------------------------
void reset_s(){ //reset_s THE GAME
#ifdef DEBUG
Serial.println("FULL reset_s");
#endif

  Serial.println("SEQUENCE_RESET");
  
 if (OUTPUT_MODE == MAGLOCK_s){
  digitalWrite(RELAY_PIN_s, HIGH);  
 }
 if (OUTPUT_MODE == LEDLIGHT_s){
  digitalWrite(RELAY_PIN_s, LOW);  
 }
  gameWON_s = false;
  state_s=0;
  reset_sstate_s = 0;
  flashLEDS_s(4,50);
  
}

//----------- FLASH LEDS -----------------------------------------------
void flashLEDS_s(int cycles , int wait)
{
  ledsOFF_s();
    for(int i=0 ; i<=cycles ; i++){
    ledsON_s();
    delay(wait);
    ledsOFF_s();
    delay(wait);
  }
  
}


//----------- LEDS ON -----------------------------------------------
void ledsOFF_s()
{
  digitalWrite(LEDPIN_1_s,LOW);
  digitalWrite(LEDPIN_2_s,LOW);
  digitalWrite(LEDPIN_3_s,LOW);
  digitalWrite(LEDPIN_4_s,LOW);
  digitalWrite(LEDPIN_5_s,LOW);
  digitalWrite(LEDPIN_6_s,LOW);
  digitalWrite(LEDPIN_7_s,LOW);
}
//----------- LEDS OFF -----------------------------------------------
void ledsON_s()
{
  digitalWrite(LEDPIN_1_s,HIGH);
  digitalWrite(LEDPIN_2_s,HIGH);
  digitalWrite(LEDPIN_3_s,HIGH);
  digitalWrite(LEDPIN_4_s,HIGH);
  digitalWrite(LEDPIN_5_s,HIGH);
  digitalWrite(LEDPIN_6_s,HIGH);
  digitalWrite(LEDPIN_7_s,HIGH);
}









//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------









// ***************** SEQ CODE - END ********************************************************************* 

//=========================== FUNCTIONS ======================================================

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

//----------- GET INPUT -----------------------------------------------
void getInput(int _input){
#ifdef DEBUG
Serial.println("GOT INPUT");
#endif

  /*
 CIRCLE #1 : 1 , 4 , 8 , 9, 6 , 2
 CIRCLE #2 : 2 , 5 , 9 , 10, 7 , 3
 CIRCLE #3 : 5 , 8 , 11 , 12, 10 , 6
 WINNING   : 2 , 5 , 6 , 8, 9 , 10
 START     :
*/
  
  bool temp1 = false;
  
  switch ( _input){
    case 0: // CIRCLE #1 -> ROTATE: 1 , 4 , 8 , 9, 6 , 2
      if(!gameWON){

       temp1 = ledFlag2;
       ledFlag2 = ledFlag6;
       ledFlag6 = ledFlag9;
       ledFlag9 = ledFlag8;
       ledFlag8 = ledFlag4;
       ledFlag4 = ledFlag1;
       ledFlag1 = temp1;
       
      }

      #ifdef DEBUG
      Serial.println('0');
      #endif
      break;
      
    case 1: // CIRCLE #2 -> ROTATE: 2 , 5 , 9 , 10V, 7 , 3
      if(!gameWON){
        
       temp1 = ledFlag3;
       ledFlag3 = ledFlag7;
       ledFlag7 = ledFlag10;
       ledFlag10 = ledFlag9;
       ledFlag9 = ledFlag5;
       ledFlag5 = ledFlag2;
       ledFlag2 = temp1;
              
      }
      #ifdef DEBUG
      Serial.println('1');
      #endif
      break;
      
    case 2: // CIRCLE #3 -> ROTATE: 5 , 8 , 11 , 12, 10 , 6
      if(!gameWON){

       temp1 = ledFlag6;
       ledFlag6 = ledFlag10;
       ledFlag10 = ledFlag12;
       ledFlag12 = ledFlag11;
       ledFlag11 = ledFlag8;
       ledFlag8 = ledFlag5;
       ledFlag5 = temp1;
       
      }

      #ifdef DEBUG
      Serial.println('2');
      #endif
      break;
      
    case 3: // RESET PUZZLE -> LEDS ONLY - if the game isn't won

    // ---------- TESTING MODE - FOR WIRING ----------
    if (STATUS == LEDTEST){
      if(buttonCycle < numLEDS){
        buttonCycle = buttonCycle + 1;
        oneLED( buttonCycle);     
      }
      else buttonCycle = 0;  
    }

    // ---------- GAME PLAY MODE ----------
    if (STATUS == GAMEPLAY){
      if(!gameWON){
        ledFlag1 = _ledFlag1;
        ledFlag2 = _ledFlag2;
        ledFlag3 = _ledFlag3;
        ledFlag4 = _ledFlag4;
        ledFlag5 = _ledFlag5;
        ledFlag6 = _ledFlag6;
        ledFlag7 = _ledFlag7;
        ledFlag8 = _ledFlag8;
        ledFlag9 = _ledFlag9;
        ledFlag10 = _ledFlag10;
        ledFlag11 = _ledFlag11;
        ledFlag12 = _ledFlag12;
      }
    }

      #ifdef DEBUG
      Serial.println('3');
      #endif

      break;
      
    case 4:  
      #ifdef DEBUG
      Serial.println('4');
      #endif
      break;
    
    case 5: 
      #ifdef DEBUG
      Serial.println('5');
      #endif
      break;  
      
    default: // DO NOTHING
      break;
  }
  
  if(!gameWON){
    updateLEDS();
    checkWin();
  }
}

//----------- UPDATE LEDS -----------------------------------------------
// update leds according to new state
void updateLEDS(){
#ifdef DEBUG
Serial.println("UPDATE LEDS");
#endif

  digitalWrite(LEDPIN_1,ledFlag1);
  digitalWrite(LEDPIN_2,ledFlag2);
  digitalWrite(LEDPIN_3,ledFlag3);
  digitalWrite(LEDPIN_4,ledFlag4);
  digitalWrite(LEDPIN_5,ledFlag5);
  digitalWrite(LEDPIN_6,ledFlag6);
  digitalWrite(LEDPIN_7,ledFlag7);
  digitalWrite(LEDPIN_8,ledFlag8);
  digitalWrite(LEDPIN_9,ledFlag9);
  digitalWrite(LEDPIN_10,ledFlag10);
  digitalWrite(LEDPIN_11,ledFlag11);
  digitalWrite(LEDPIN_12,ledFlag12);
  
}

//----------- CHECK STATE -----------------------------------------------
// checks state for WIN or LEDs OFF
void checkWin(){
#ifdef DEBUG
Serial.println("CHECK FOR THE WIN");
#endif

if(!gameWON){

  if (ledFlag2 == win_ledFlag2){
    if (ledFlag5 == win_ledFlag5){
      if (ledFlag6 == win_ledFlag6){
        if (ledFlag8 == win_ledFlag8){
          if (ledFlag9 == win_ledFlag9){
            if (ledFlag10 == win_ledFlag10){
                  // YOU WON!!!!
                  youWIN();
            }
          }
        }
      }
    }
  }
}
  
}

//----------- WINNING SEQUENCE -----------------------------------------------
void youWIN(){
  
#ifdef DEBUG
Serial.println("YOU WON");
#endif

  delay(winDelay);

  for( int i=0; i<=numLEDS ; i++){
    oneLED(i);
    updateLEDS();
    delay(100);    
  }

  

 flashLEDS(4,100);
 Serial.println("CIRCLE_WIN");

  gameWON = true;
  

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, LOW);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, HIGH);  
 }

  //reset();
  
}

//----------- RESET PUZZLE -----------------------------------------------
void reset(){    //RESET THE GAME
#ifdef DEBUG
Serial.println("FULL RESET");
#endif

  //Serial.println(" RESET ");

  gameWON = false;

// RESET LEDS TO STARTING POSTITION
  ledFlag1 = _ledFlag1;
  ledFlag2 = _ledFlag2;
  ledFlag3 = _ledFlag3;
  ledFlag4 = _ledFlag4;
  ledFlag5 = _ledFlag5;
  ledFlag6 = _ledFlag6;
  ledFlag7 = _ledFlag7;
  ledFlag8 = _ledFlag8;
  ledFlag9 = _ledFlag9;
  ledFlag10 = _ledFlag10;
  ledFlag11 = _ledFlag11;
  ledFlag12 = _ledFlag12;

// RESET RELAY STATE TO STARTING POSITION
 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }
 
 Serial.println("CIRCLE_RESET");

 flashLEDS(3,50);
 updateLEDS();
  
}

//----------- TURN ON 1 LED  -----------------------------------------------
void oneLED(int ledNum){

switch ( ledNum){
    case 0: 
      ledsOFF();
    break;
    
    case 1: 
      ledFlag1 = true;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 2: 
      ledFlag1 = false;
      ledFlag2 = true;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 3: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = true;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 4: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = true;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 5: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = true;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 6: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = true;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 7: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = true;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 8: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = true;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 9: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = true;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 10: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = true;
      ledFlag11 = false;
      ledFlag12 = false;
    break;
    
    case 11: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = true;
      ledFlag12 = false;
    break;
    
    case 12: 
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
      ledFlag8 = false;
      ledFlag9 = false;
      ledFlag10 = false;
      ledFlag11 = false;
      ledFlag12 = true;
    break;
    
      
    default:
    break;

    //updateLEDS();
 }   
}

//----------- SET WIN - FOR TESTING -----------------------------------------------
void setWin(){
#ifdef DEBUG
Serial.println("SET WIN - FAKED");
#endif

  ledFlag1 = win_ledFlag1;
  ledFlag2 = win_ledFlag2;
  ledFlag3 = win_ledFlag3;
  ledFlag4 = win_ledFlag4;
  ledFlag5 = win_ledFlag5;
  ledFlag6 = win_ledFlag6;
  ledFlag7 = win_ledFlag7;
  ledFlag8 = win_ledFlag8;
  ledFlag9 = win_ledFlag9;
  ledFlag10 = win_ledFlag10;
  ledFlag11 = win_ledFlag11;
  ledFlag12 = win_ledFlag12;  
}
          
//----------- FLASH LEDS -----------------------------------------------
void flashLEDS(int cycles , int wait)
{
  ledsOFF();
    for(int i=0 ; i<=cycles ; i++){
    ledsON();
    delay(wait);
    ledsOFF();
    delay(wait);
  }
  
}

//----------- LEDS ON -----------------------------------------------
void ledsOFF()
{
  digitalWrite(LEDPIN_1,LOW);
  digitalWrite(LEDPIN_2,LOW);
  digitalWrite(LEDPIN_3,LOW);
  digitalWrite(LEDPIN_4,LOW);
  digitalWrite(LEDPIN_5,LOW);
  digitalWrite(LEDPIN_6,LOW);
  digitalWrite(LEDPIN_7,LOW);
  digitalWrite(LEDPIN_8,LOW);
  digitalWrite(LEDPIN_9,LOW);
  digitalWrite(LEDPIN_10,LOW);
  digitalWrite(LEDPIN_11,LOW);
  digitalWrite(LEDPIN_12,LOW);
}
//----------- LEDS OFF -----------------------------------------------
void ledsON()
{
  digitalWrite(LEDPIN_1,HIGH);
  digitalWrite(LEDPIN_2,HIGH);
  digitalWrite(LEDPIN_3,HIGH);
  digitalWrite(LEDPIN_4,HIGH);
  digitalWrite(LEDPIN_5,HIGH);
  digitalWrite(LEDPIN_6,HIGH);
  digitalWrite(LEDPIN_7,HIGH);
  digitalWrite(LEDPIN_8,HIGH);
  digitalWrite(LEDPIN_9,HIGH);
  digitalWrite(LEDPIN_10,HIGH);
  digitalWrite(LEDPIN_11,HIGH);
  digitalWrite(LEDPIN_12,HIGH);
}









//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
