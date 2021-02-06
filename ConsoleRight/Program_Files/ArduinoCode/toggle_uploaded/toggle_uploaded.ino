// PUZZLE : Seven Toggle Switch

// DATE CREATED: 6/29/18
// DATE CREATED: 10/11/18
// LAST DATE EDITED: 12/14/18

// PREVIOUS CODE : Alien Keypad

// NOTES:

//----------- DEFINES -------------------------------------------------------------

//#define DEBUG

#define TESTING 0
#define XEASY 1
#define EASY 0
#define MEDIUM 0
#define HARD 0
#define OLDHARD 0
// set the mode here
#define SKILL XEASY 

#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 

#define numButtons 8
#define RELAY_PIN 6

#define ButtonPin_1 2
#define ButtonPin_2 3
#define ButtonPin_3 4
#define ButtonPin_4 5
#define ButtonPin_5 6
#define ButtonPin_6 7
#define ButtonPin_7 8

#define ResetButton 9


#define ledPin1  10
#define ledPin2  11
#define ledPin3  12
#define ledPin4  13
#define ledPin5  A1
#define ledPin6  A2
#define ledPin7  A3
#define ledPin8  A4

// ---------- STARTING STATE OF LEDS ----------
bool ledFlag1 = false;
bool ledFlag2 = false;
bool ledFlag3 = false;
bool ledFlag4 = false;
bool ledFlag5 = false;
bool ledFlag6 = false;
bool ledFlag7 = false;
bool ledFlag8 = false;

bool firstLoop = true;

/*
const int ButtonPin1 = 2;
const int ButtonPin2 = 3;
const int ButtonPin3 = 4;
const int ButtonPin4 = 5;
const int ButtonPin5 = 6;
const int ButtonPin6 = 7;
const int ButtonPin7 = 8;
const int ButtonPin8 = 16;

int ledPin1 = 9;
int ledPin2 = 10;
int ledPin3 = 11;
int ledPin4 = 12;
int ledPin5 = 13;
int ledPin6 = 14;
int ledPin7 = 15;
int ledPin8 = 17;
*/


//----------- FUNCTIONS -------------------------------------------------------------

void updateLEDs();
void buttonToggled(int );
void youWIN();
void checkWin();
void reset();
void toggle( int  , int  , int  , int  );
void toggle( int  , int  , int  );
void toggle( int  , int  );
void toggle( int  );

void ledsON();
void ledsOFF();
void flashLEDS(int  , int );

void fullReset();
void checkReset(int );

//---- Serial Communication ----
char Comp(char* );

//----------- VARIABLES -------------------------------------------------------------

//---- Serial Communication ----
char inData[20];
char inChar=-1;
byte index = 0;
int incoming_state = 0;
char incoming_char = 0;

bool gameWON = false;

bool fakeReset = false;
bool fakeWin = false;
bool resetHigh = false;
int resetCount = 0;

unsigned long debounceDelay = 50; // Increase is there is to much noise
unsigned long lastDebounceTime = 0;

int bufferVal[numButtons];
int buttonState[numButtons];
int lastState[numButtons];

//=========================== SETUP ==========================================================
void setup() {

  Serial.begin(9600);

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
  pinMode(ButtonPin_4,INPUT);
  pinMode(ButtonPin_5,INPUT);
  pinMode(ButtonPin_6,INPUT);
  pinMode(ButtonPin_7,INPUT);
  pinMode(ResetButton,INPUT);

//---------------LEDS--------------- 
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
  pinMode(ledPin7,OUTPUT);
  pinMode(ledPin8,OUTPUT);


  digitalWrite(ledPin1,ledFlag1);
  digitalWrite(ledPin2,ledFlag2);
  digitalWrite(ledPin3,ledFlag3);
  digitalWrite(ledPin4,ledFlag4);
  digitalWrite(ledPin5,ledFlag5);
  digitalWrite(ledPin6,ledFlag6);
  digitalWrite(ledPin7,ledFlag7);
  digitalWrite(ledPin8,ledFlag8);
  
  if( SKILL == XEASY){
   // Serial.println(" SKILL LEVEL : EXTRA EASY ");
  }
  if( SKILL == EASY){
    //Serial.println(" SKILL LEVEL : EASY ");
  }
  if( SKILL == MEDIUM){
    //Serial.println(" SKILL LEVEL : MEDIUM ");
  }
  if( SKILL == HARD){
   // Serial.println(" SKILL LEVEL : HARD ");
  }

  
//bufferVal[0] = digitalRead(ButtonPin_1);
//bufferVal[1] = digitalRead(ButtonPin_2);
//bufferVal[2] = digitalRead(ButtonPin_3);
//bufferVal[3] = digitalRead(ButtonPin_4);
//bufferVal[4] = digitalRead(ButtonPin_5);
//bufferVal[5] = digitalRead(ButtonPin_6);
//bufferVal[6] = digitalRead(ButtonPin_7);
//bufferVal[7] = digitalRead(ResetButton);

  

}


//=========================== MAIN LOOP ======================================================
void loop() {
  
 if(firstLoop){
    delay(1000);
    Serial.println("TOGGLE_RESET");
    firstLoop = false;

    buttonState[0] = bufferVal[0];
    buttonState[1] = bufferVal[1];
    buttonState[2] = bufferVal[2];
    buttonState[3] = bufferVal[3];
    buttonState[4] = bufferVal[4];
    buttonState[5] = bufferVal[5];
    buttonState[6] = bufferVal[6];
    buttonState[7] = bufferVal[7];
    
  }
  
  
 // ---- Serial Communication - Phone Win ----
// received a command from the Pi

if (Comp ("togSOLVED") == 0){
  fakeWin = true;
  
  ledFlag1 = true;
  ledFlag2 = true;
  ledFlag3 = true;
  ledFlag4 = true;
  ledFlag5 = true;
  ledFlag6 = true;
  ledFlag7 = true;
  checkWin();
}
else if (Comp ("togRESET") == 0){
  fakeReset=true;  
  fullReset();
}



bufferVal[0] = digitalRead(ButtonPin_1);
bufferVal[1] = digitalRead(ButtonPin_2);
bufferVal[2] = digitalRead(ButtonPin_3);
bufferVal[3] = digitalRead(ButtonPin_4);
bufferVal[4] = digitalRead(ButtonPin_5);
bufferVal[5] = digitalRead(ButtonPin_6);
bufferVal[6] = digitalRead(ButtonPin_7);
bufferVal[7] = digitalRead(ResetButton);

  
  for( int i=0 ; i<numButtons ; i++ ){  

    if ( bufferVal[i] != lastState[i]){ // Switch changed, due to noise or press
      lastDebounceTime = millis();
      //Serial.print(" Reset Debounce Timer ");} // Reset the debounce timer
    }
      
    if((millis() - lastDebounceTime) > debounceDelay){ // Change has been longer that debounce delay
      //Serial.print(" Change Long Enough ");
      
      if(i==7){
        if (buttonState[i] == HIGH){
          resetHigh=true;
        }  
        else if (buttonState[i] == LOW){
          resetHigh=false;
        }
      checkReset(i);
      }
     
      if (bufferVal[i] != buttonState[i]){ // If the button state changed
        buttonState[i] = bufferVal[i]; // Take the bufferVal as new State
        //Serial.print(" Button State is officaially changed ");
        //Serial.println("State Changed");
        
        if (!gameWON) buttonToggled(i);
        
//        if (buttonState[i] == HIGH){
//          resetHigh=true;
//          buttonToggled(i);      
//        }  
//        else if (buttonState[i] == LOW){
//          resetHigh=false;
//          buttonToggled(i);
//        }
        
      }
    }
    lastState[i] = bufferVal[i]; // Save values for next loop
  }

if( !gameWON){
  checkWin();
}
  
}


//================================================================= FUNCTIONS ======================================================


void checkReset(int _input){
  
  if(resetHigh){
    delay(50);
      resetCount++;
      //Serial.println(resetCount);
    if(resetCount>50){
        fullReset();
      }

  }
  else if(!resetHigh){
    resetCount=0;
  }  
}



//----------- FULL RESET -----------------------------------------------
void fullReset(){
  
   if(!fakeReset) Serial.println("TOGGLE_RESET");

   flashLEDS(5 , 70);
   resetCount=0;        
   gameWON = false;      
   fakeWin = false;
   fakeReset = false;   

    
 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }

  
}

//----------- RESET PUZZLE -----------------------------------------------
void reset(){
  

      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
}



//----------- WINNING SEQUENCE -----------------------------------------------
void youWIN(){
   gameWON = true;

  if(!fakeWin) Serial.println("TOGGLE_WIN");
 

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, LOW);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, HIGH);  
 }

 flashLEDS(4 , 200);
 reset();
 ledsON();

   // RESET THE PUZZLE------

  
}

//----------- CHECK WIN -----------------------------------------------
void checkWin(){
  if (ledFlag1 == true){
    if (ledFlag2 == true){
      if (ledFlag3 == true){
        if (ledFlag4 == true){
          if (ledFlag5 == true){
            if (ledFlag6 == true){
              if (ledFlag7 == true){
                youWIN();
                
              }
            }
          }
        }
      }
    }
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

//----------- GET INPUT - BUTTON TOGGLED -----------------------------------------------
void buttonToggled(int _input){

  if(_input == 7){ // RESET THE LEDS
    #ifdef DEBUG
      Serial.println(" RESET ");
    #endif
    

    
    Serial.println(" RESET BUTTON");
      ledFlag1 = false;
      ledFlag2 = false;
      ledFlag3 = false;
      ledFlag4 = false;
      ledFlag5 = false;
      ledFlag6 = false;
      ledFlag7 = false;
    
  }

// ========== SKILL : TESTING ==========
// 

if( SKILL == TESTING){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : TESTING ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 0 : toggle( 1 );
    break;
     
  case 1 : toggle( 2 );
    break;
      
  case 2 : toggle( 3 );
    break;
      
  case 3 : toggle( 4 );
    break;
      
  case 4 : toggle( 5 );
    break;
      
  case 5 : toggle( 6 );
    break;
      
  case 6 : toggle( 7 );
    break;

  default:
    break;
  }
  }
// ===================================

// ---------- SKILL LEVELS : XEASY , EASY , MEDIUM , HARD ----------

// ========== SKILL : EXTRA EASY ==========
// OFF SWITCHES: 1 , 2 , 5

if( SKILL == XEASY){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : EXTRA EASY ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 0 : toggle( 1 , 2 );
    break;
     
  case 1 : toggle( 4 , 5 );
    break;
      
  case 2 : toggle( 1 , 2 , 3 , 4 );
    break;
      
  case 3 : toggle( 1 , 2 , 5 );
    break;
      
  case 4 : toggle( 2 , 4 );
    break;
      
  case 5 : toggle( 2 , 6  );
    break;
      
  case 6 : toggle( 1 , 7 );
    break;

  default:
    break;
  }
  }
// ===================================


// ========== SKILL : EASY ==========
// OFF SWITCHES: 1 , 6

if( SKILL == EASY){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : EASY ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 0 : toggle( 1 , 7 );
    break;
     
  case 1 : toggle( 2 , 6 );
    break;
      
  case 2 : toggle( 1 , 2 , 3 , 4 );
    break;
      
  case 3 : toggle( 5 );
    break;
      
  case 4 : toggle( 1 , 2 , 4 );
    break;
      
  case 5 : toggle( 4 );
    break;
      
  case 6 : toggle( 1 , 4 , 7 );
    break;

  default:
    break;
  }
  }
// ===================================

// ========== SKILL : MEDIUM ==========
// OFF SWITCHES: 2 , 4 , 7

if( SKILL == MEDIUM){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : MEDIUM ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 0 : toggle( 4 , 6 , 7 );
    break;
     
  case 1 : toggle( 2 , 4 , 6 );
    break;
      
  case 2 : toggle( 3 );
    break;
      
  case 3 : toggle( 1 , 2 );
    break;
      
  case 4 : toggle( 1 , 2 , 4 , 6  );
           toggle( 7 );
    break;
      
  case 5 : toggle( 4 , 5 , 6 , 7 );
    break;
      
  case 6 : toggle( 1 , 7 );
    break;

  default:
    break;
  }
  }
// ===================================

// ========== SKILL : HARD ==========
// OFF SWITCHES: 2 , 3 , 5 , 7

if( SKILL == HARD){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : HARD ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 0 : toggle( 2 , 3 , 7 );
    break;
     
  case 1 : toggle( 2 , 3 , 5 );
    break;
      
  case 2 : toggle( 1 , 3 , 4 , 7 );
    break;
      
  case 3 : toggle( 3 , 4 , 5 );
    break;
      
  case 4 : toggle( 2 , 5 );
    break;
      
  case 5 : toggle( 1 , 3 , 6 );
    break;
      
  case 6 : toggle( 1 , 5 , 6 , 7 );
    break;

  default:
    break;
  }
  }

// ========== SKILL : OLDHARD ==========

if( SKILL == OLDHARD){
#ifdef DEBUG
  Serial.println(" SKILL LEVEL : OLDHARD ");
  Serial.println(_input);
#endif
  
switch(_input){
  
  case 1 : // LED: 2,3,7
      Serial.println("Case 1");
      ledFlag2 = !ledFlag2;
      ledFlag3 = !ledFlag3;
      ledFlag7 = !ledFlag7;
      break;
     
  case 2 : // LED: 2,3,5
      Serial.println("Case 2");
      ledFlag2 = !ledFlag2;
      ledFlag3 = !ledFlag3;
      ledFlag5 = !ledFlag5;
      break;
      
  case 3 : // LED: 1,3,4,7
      Serial.println("Case 3");
      ledFlag1 = !ledFlag1;
      ledFlag3 = !ledFlag3;
      ledFlag4 = !ledFlag4;
      ledFlag7 = !ledFlag7;
      break;
      
  case 4 : // LED: 3,4,5  
      Serial.println("Case 4");
      ledFlag3 = !ledFlag3;
      ledFlag4 = !ledFlag4;
      ledFlag5 = !ledFlag5;
      break;
      
  case 5 : // LED: 2,5
      Serial.println("Case 5");
      ledFlag2 = !ledFlag2;
      ledFlag5 = !ledFlag5;
      break;
      
  case 6 : // LED: 1,6,7 === 1,3,7
      Serial.println("Case 6");
      ledFlag1 = !ledFlag1;
      ledFlag3 = !ledFlag3;
      ledFlag7 = !ledFlag7;
      break;
      
  case 7 : // LED: 1,5,6,7  
      Serial.println("Case 3");
      ledFlag1 = !ledFlag1;
      ledFlag5 = !ledFlag5;
      ledFlag6 = !ledFlag6;
      ledFlag7 = !ledFlag7;
      break;

  default:
    break;
  }
  }
// ===================================

  updateLEDs();

}

//----------- UPDATE LEDS -----------------------------------------------
void updateLEDs(){
  digitalWrite(ledPin1,ledFlag1);
  digitalWrite(ledPin2,ledFlag2);
  digitalWrite(ledPin3,ledFlag3);
  digitalWrite(ledPin4,ledFlag4);
  digitalWrite(ledPin5,ledFlag5);
  digitalWrite(ledPin6,ledFlag6);
  digitalWrite(ledPin7,ledFlag7);
  digitalWrite(ledPin8,ledFlag8);
}


//----------- TOGGLE LEDS -----------------------------------------------
//----------- TOGGLE 4 LEDS -------------
void toggle( int _led1 , int _led2 , int _led3 , int _led4){
  switch(_led1){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led2){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led3){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led4){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
}

//----------- TOGGLE 3 LEDS -------------
void toggle( int _led1 , int _led2 , int _led3 ){
  switch(_led1){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led2){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led3){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
}

//----------- TOGGLE 2 LEDS -------------
void toggle( int _led1 , int _led2){
  switch(_led1){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
  switch(_led2){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
}

//----------- TOGGLE 2 LEDS -------------
void toggle( int _led1){
  switch(_led1){
    case 1: ledFlag1 = !ledFlag1;
    break;
    case 2: ledFlag2 = !ledFlag2;
    break;
    case 3: ledFlag3 = !ledFlag3;
    break;
    case 4: ledFlag4 = !ledFlag4;
    break;
    case 5: ledFlag5 = !ledFlag5;
    break;
    case 6: ledFlag6 = !ledFlag6;
    break;
    case 7: ledFlag7 = !ledFlag7;
    break;
    default:
    break;
  }
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
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);
  digitalWrite(ledPin5,LOW);
  digitalWrite(ledPin6,LOW);
  digitalWrite(ledPin7,LOW);

}
//----------- LEDS OFF -----------------------------------------------
void ledsON()
{
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledPin5,HIGH);
  digitalWrite(ledPin6,HIGH);
  digitalWrite(ledPin7,HIGH);

}

//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
