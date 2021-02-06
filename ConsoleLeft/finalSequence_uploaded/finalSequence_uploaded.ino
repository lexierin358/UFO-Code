#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 

#define numButtons 16
#define RELAY_PIN 6

#define ButtonPinR_1 23    // Red Booster
#define ButtonPinR_2 25    // Red Thruster
#define ButtonPinR_3 27    // Red Reactor

#define ButtonPinR_4 29    // Red Large
#define ButtonPinR_5 31    // Red Proellant
#define ButtonPinR_6 33    // Red Coolant
#define ButtonPinR_7 35    // R - Elevation Up
#define ButtonPinR_8 37    // R - Elevation Down

#define ButtonPinY_1 22    // Yellow Booster
#define ButtonPinY_2 24    // Yellow Thruster
#define ButtonPinY_3 26    // Yellow Reactor

#define ButtonPinY_4 28    // Yellow Large
#define ButtonPinY_5 30    // Yellow Proellant
#define ButtonPinY_6 32    // Yellow Coolant
#define ButtonPinY_7 34    // Y - Elevation Up
#define ButtonPinY_8 36    // Y - Elevation Down

//#define ButtonPinR_1 22    // Red Booster
//#define ButtonPinR_2 24    // Red Thruster
//#define ButtonPinR_3 26    // Red Reactor
//
//#define ButtonPinR_4 28    // Red Large
//#define ButtonPinR_5 30    // Red Proellant
//#define ButtonPinR_6 32    // Red Coolant
//#define ButtonPinR_7 34    // R - Elevation Up
//#define ButtonPinR_8 36    // R - Elevation Down
//
//#define ButtonPinY_1 23    // Yellow Booster
//#define ButtonPinY_2 25    // Yellow Thruster
//#define ButtonPinY_3 27    // Yellow Reactor
//
//#define ButtonPinY_4 29    // Yellow Large
//#define ButtonPinY_5 31    // Yellow Proellant
//#define ButtonPinY_6 33    // Yellow Coolant
//#define ButtonPinY_7 35    // Y - Elevation Up
//#define ButtonPinY_8 37    // Y - Elevation Down


#define ledPinR_1  47
#define ledPinR_2  39
#define ledPinR_3  41
#define ledPinR_4  43
#define ledPinR_5  45

#define ledPinY_1  38
#define ledPinY_2  40
#define ledPinY_3  42
#define ledPinY_4  44
#define ledPinY_5  46



#define ResetButton 9


// ---------- STARTING STATE OF LEDS ----------
bool ledFlag1 = false;
bool ledFlag2 = false;
bool ledFlag3 = false;
bool ledFlag4 = false;
bool ledFlag5 = false;
bool ledFlag6 = false;
bool ledFlag7 = false;
bool ledFlag8 = false;


bool bFlagR_1 = false;
bool bFlagR_2 = false;
bool bFlagR_3 = false;
bool bFlagR_4 = false;
bool bFlagR_5 = false;
bool bFlagR_6 = false;
bool bFlagR_7 = false;
bool bFlagR_8 = false;

bool bFlagY_1 = false;
bool bFlagY_2 = false;
bool bFlagY_3 = false;
bool bFlagY_4 = false;
bool bFlagY_5 = false;
bool bFlagY_6 = false;
bool bFlagY_7 = false;
bool bFlagY_8 = false;

bool firstLoop = true;
bool gameWON = false;

//===========================================================

bool phase_1 = false;
bool phase_2 = false;
bool phase_3 = false;
bool phase_4 = false;

int elevation_R_count = 0;
int elevation_Y_count = 0;

int ph3_state = 0;

//===========================================================


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

void checkState();
void getInput(int);

void setLow(int);

bool fakePhase_1 = false;
bool fakePhase_2 = false;
bool fakePhase_3 = false;
bool fakeWin = false;
bool fakeReset = false;

//---- Serial Communication ----
char Comp(char* );

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
  pinMode(ButtonPinR_1,INPUT); 
  pinMode(ButtonPinR_2,INPUT);
  pinMode(ButtonPinR_3,INPUT);
  pinMode(ButtonPinR_4,INPUT);
  pinMode(ButtonPinR_5,INPUT);
  pinMode(ButtonPinR_6,INPUT);
  pinMode(ButtonPinR_7,INPUT);
  pinMode(ButtonPinR_8,INPUT);
  
  pinMode(ButtonPinY_1,INPUT); 
  pinMode(ButtonPinY_2,INPUT);
  pinMode(ButtonPinY_3,INPUT);
  pinMode(ButtonPinY_4,INPUT);
  pinMode(ButtonPinY_5,INPUT);
  pinMode(ButtonPinY_6,INPUT);
  pinMode(ButtonPinY_7,INPUT);
  pinMode(ButtonPinY_8,INPUT);
  
  
  pinMode(ResetButton,INPUT);

//---------------LEDS--------------- 
  pinMode(ledPinR_1,OUTPUT);
  pinMode(ledPinR_2,OUTPUT);
  pinMode(ledPinR_3,OUTPUT);
  pinMode(ledPinR_4,OUTPUT);
  pinMode(ledPinR_5,OUTPUT);
  
  
//  pinMode(ledPinR_6,OUTPUT);
//  pinMode(ledPinR_7,OUTPUT);
//  pinMode(ledPin8,OUTPUT);


//  digitalWrite(ledPin1,ledFlag1);
//  digitalWrite(ledPin2,ledFlag2);
//  digitalWrite(ledPin3,ledFlag3);
//  digitalWrite(ledPin4,ledFlag4);
//  digitalWrite(ledPin5,ledFlag5);
//  digitalWrite(ledPin6,ledFlag6);
//  digitalWrite(ledPin7,ledFlag7);
//  digitalWrite(ledPin8,ledFlag8);
  
  
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
 
// startFINAL 1_DONE 2_DONE 3_DONE winFINAL resetFinal
  
if (Comp ("startFINAL") == 0){
  //Serial.println("PHASE_0");
}
else if (Comp ("1_DONE") == 0){
  
  bFlagR_1==HIGH;
  bFlagR_3==HIGH;
  bFlagY_1==HIGH;
  bFlagY_3==HIGH;
  bFlagR_2==LOW;
  bFlagY_2==LOW;
  
  //phase_1 = false;
  
  checkState();
  

}
else if (Comp ("2_DONE") == 0){
  elevation_Y_count==3;
  elevation_R_count==5;
  
  checkState();
}
else if (Comp ("3_DONE") == 0){
  ph3_state==2;

}
else if (Comp ("winFINAL") == 0){

}
else if (Comp ("resetFinal") == 0){
  
 phase_1 = false;
 phase_2 = false;
 phase_3 = false;
 phase_4 = false;

 elevation_R_count = 0;
 elevation_Y_count = 0;

 ph3_state = 0;
 
 Serial.println("FINAL_RESET");
  

}
else{
  //NULL
}

bufferVal[0] = digitalRead(ButtonPinR_1);
bFlagR_1=bufferVal[0];

bufferVal[1] = digitalRead(ButtonPinR_2);
bFlagR_2=bufferVal[1];

bufferVal[2] = digitalRead(ButtonPinR_3);
bFlagR_3=bufferVal[2];

bufferVal[3] = digitalRead(ButtonPinR_4);
bFlagR_4=bufferVal[3];

bufferVal[4] = digitalRead(ButtonPinR_5);
bFlagR_5=bufferVal[4];

bufferVal[5] = digitalRead(ButtonPinR_6);
bFlagR_6=bufferVal[5];

bufferVal[6] = digitalRead(ButtonPinR_7);
bFlagR_7=bufferVal[6];

bufferVal[7] = digitalRead(ButtonPinR_8);
bFlagR_8=bufferVal[7];



bufferVal[8] = digitalRead(ButtonPinY_1);
bFlagY_1=bufferVal[8];

bufferVal[9] = digitalRead(ButtonPinY_2);
bFlagY_2=bufferVal[9];

bufferVal[10] = digitalRead(ButtonPinY_3);
bFlagY_3=bufferVal[10];

bufferVal[11] = digitalRead(ButtonPinY_4);
bFlagY_4=bufferVal[11];

bufferVal[12] = digitalRead(ButtonPinY_5);
bFlagY_5=bufferVal[13];

bufferVal[13] = digitalRead(ButtonPinY_6);
bFlagY_6=bufferVal[14];

bufferVal[14] = digitalRead(ButtonPinY_7);
bFlagY_7=bufferVal[15];

bufferVal[15] = digitalRead(ButtonPinY_8);
bFlagY_8=bufferVal[16];

  if(firstLoop){
    
  //Serial.println("PHASE_0");
  Serial.println("FINAL_RESET");
  firstLoop = false;

//  buttonState[0] = bufferVal[0];
//  buttonState[1] = bufferVal[1];
//  buttonState[2] = bufferVal[2];
//  buttonState[3] = bufferVal[3];
//  buttonState[4] = bufferVal[4];
//  buttonState[5] = bufferVal[5];
//  buttonState[6] = bufferVal[6];
//  buttonState[7] = bufferVal[7];
//  
//  buttonState[8] = bufferVal[8];
//  buttonState[9] = bufferVal[9];
//  buttonState[10] = bufferVal[10];
//  buttonState[11] = bufferVal[11];
//  buttonState[12] = bufferVal[12];
//  buttonState[13] = bufferVal[13];
//  buttonState[14] = bufferVal[14];
//  buttonState[15] = bufferVal[15];
  
  delay(2000);
 
      
  }

// ---- Serial Communication - Phone Win ----
// received a command from the Pi



  



  
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
        //Serial.println("State Changed");
        //buttonToggled(i);
        
       if (buttonState[i] == HIGH){ // If  the button is Pressed          
          getInput(i);
         //Serial.print("Button Pressed: ");
          //Serial.println(i);
        }
       if (buttonState[i] == LOW){
         setLow(i);
       }
        
        //if (buttonState[i] == HIGH)  buttonToggled(i);        
        //else if (buttonState[i] == LOW)  buttonToggled(i);
        
      }
    }
    lastState[i] = bufferVal[i]; // Save values for next loop
  }


  
}


//================================================================= FUNCTIONS ======================================================
//----------- SET LOW -----------------------------------------------

void setLow(int _input){
  
  
  switch ( _input){
    case 0: 
      bFlagR_1 = false;
      //Serial.println("Toggle 1 - OFF");
      break;
      
    case 1: 
      bFlagR_2 = false;
      //Serial.println("Toggle 2 - OFF");
      break;
      
    case 2:  
      bFlagR_3 = false;
     // Serial.println("Toggle 3 - OFF");
      break;
      
    case 3: 
      bFlagR_4 = false;
     // Serial.println(" 4 - OFF ");
      break;
      
    case 4:  
      bFlagR_5 = false;
     // Serial.println(" 5 - OFF ");
      break;
      
    case 5: 
      bFlagR_6 = false;
     // Serial.println(" 6 - OFF ");
      break;
      
    case 6: 
      bFlagR_7 = false; 
     // Serial.println(" 7 - OFF ");
      break;

 //----------------------------------------------
    case 7: 
      bFlagR_8 = false;
     // Serial.println(" 8 - OFF ");
      break;
      
      
// ============= RED BUTTONS ==================

    case 8: 
     bFlagY_1 = false;
      //Serial.println(" 9 - OFF ");
      break;
    case 9: 
      bFlagY_2 = false;
      //Serial.println("10 - OFF ");
      break;
    case 10: 
      bFlagY_3 = false;
      //Serial.println("11 - OFF ");
      break;
    case 11: 
      bFlagY_4 = false;
      //Serial.println("12 - OFF ");
      break;
    case 12: 
      bFlagY_5 = false;
      //Serial.println("13 - OFF ");
      break;
    case 13: 
      bFlagY_6 = false;
      //Serial.println("14 - OFF ");
      break;
    case 14: 
      bFlagY_7 = false;
      //Serial.println("15 - OFF ");
      break;  
    case 15: 
      bFlagY_8 = false;
     // Serial.println("16 - OFF ");
      break;  
      
    default: // DO NOTHING
      break;
  }
  
  checkState();
  
  
  
}





//----------- GET INPUT -----------------------------------------------
void getInput(int _input){
#ifdef DEBUG
Serial.println("GOT INPUT");
#endif



  switch ( _input){
    //=================================== Yellow Buttons =================================
    case 0: // YELLOW BOOSTER
      bFlagR_1 = true;
      //Serial.println("Toggle 1");
      break;
      
    case 1: // YELLOW BOOSTER
      bFlagR_2 = true;
      if(phase_2 && !phase_3){
        if(ph3_state==0){
          ph3_state=1;
        }
        else{
          ph3_state=0;
        }
       }
     // Serial.println("Toggle 2");
      break;
      
    case 2: // YELLOW THRUSTER
      bFlagR_3 = true;
     // Serial.println("Toggle 3");
      break;
      
    case 3: // YELLOW REACTOR
      bFlagR_4 = true;     
     // Serial.println('4');
      break;
      
    case 4: //YELLOW LAUNCH BUTTON
      bFlagR_5 = true;
     // Serial.println('5');
      break;
      
    case 5: // YELLOW PROPELLANT
      bFlagR_6 = true;
     // Serial.println('6');
      break;
      
    case 6: // YELLOW COOLANT
      bFlagR_7 = true;
      //Serial.println('7');
      break;

    case 7: //YELLOW ELEVATION - UP
      bFlagR_8 = true;
      if(phase_1 && !phase_2){
        if(elevation_Y_count<3){          
          elevation_Y_count=elevation_Y_count+1;  
          //Serial.println("Yellow count++");  
        }   
      }
      //Serial.println('8');
      break;
    case 8: // YELlOW ELEVATION - DOWN
      bFlagY_1 = true;
     // Serial.println('9');
      break;
    case 9: 
      bFlagY_2 = true;
       if(phase_2 && !phase_3){
        if(ph3_state==1){
          ph3_state=2;
        }
        else{
          ph3_state=0;
        }
       }
      //Serial.println("10");
      break;
    case 10:
     bFlagY_3 = true; 
     // Serial.println("11");
      break;
    case 11:
     bFlagY_4 = true; 
     // Serial.println("12");
      break;
    case 12: 
      bFlagY_5 = true;
     // Serial.println("13");
      break;
    case 13: 
      bFlagY_6 = true;
     // Serial.println("14");
      break;
    case 14: 
      bFlagY_7 = true;
      if(phase_1 && !phase_2){
        if(elevation_R_count<5){          
        elevation_R_count ++;
    //Serial.println("Red count++");    
        }   
      }
      //Serial.println("15");
      break;  
    case 15: 
      bFlagY_8 = true;
     // Serial.println("16");
      break;  
      
    default: // DO NOTHING
      break;
  }
  
  checkState();
  
  
  
 
#ifdef DEBUG
Serial.println("CURRENT state_s: ");
Serial.print(state_s);
Serial.println();
#endif

  //checkState();
}


//----------- CHECK state_s -----------------------------------------------
// checks state_s for WIN or LEDs OFF
void checkState(){
#ifdef DEBUG
Serial.println("CHECK state_s");
#endif

if(!phase_1){
if(bFlagR_1==HIGH && bFlagR_3==HIGH){
  if(bFlagY_1==HIGH && bFlagY_3==HIGH){
      if(bFlagR_2==LOW && bFlagY_2==LOW){
       // Serial.println("PHASE - 2 ");
        //Serial.println("----->  Increase Left Engine Elevation by 5 and decrease Right Elevation 3");
        phase_1=true;
        Serial.println("PHASE_1");
    
     }    
  }
  
}
}

if(phase_1 && !phase_2){
  if(elevation_Y_count!=3){
       //Serial.print("Elevation Count Red: ");
       //Serial.println(elevation_R_count);
       //Serial.print("Elevation Count Yeloow: ");
       //Serial.println(elevation_Y_count);
     }
  else if (elevation_Y_count==3 && elevation_R_count==5 ){
      // Serial.println("PHASE - 3 ");
      // Serial.println("----->  Engage Right Thruster and then Left Thruster");
       elevation_R_count = 0;
       elevation_Y_count = 0;
       phase_2=true; 
       Serial.println("PHASE_2");       
     }
  
}
if(phase_2 && !phase_3){
  if(ph3_state==2){
     //  Serial.println("PHASE - 4 ");
      // Serial.println("----->  Must press both Start buttons to Launch");
       phase_3=true;
       Serial.println("PHASE_3");
     }  
}

if(phase_3 && !phase_4){
  if(bFlagR_4==HIGH && bFlagY_4==HIGH){
       //Serial.println("Congratulation - You are now on PHASE - 4 ");
       phase_4=true;
       Serial.println("PHASE_4");
     }  
}

if(phase_4){
   //Serial.println("----->  Hold on, Spaceship is taking off!!!");
   
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


  

