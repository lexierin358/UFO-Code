//FINAL CODE FOR SLIDE POTS

// DATE CREATED: UNKNOWN
// LAST DATE EDITED: 11/16/19

// PUZZLE: SLIDE POT

// ORIGINAL CODE: slide_pot1
// NOTES: orginal code testing, but only included 1 slide pot
// code is wrote to turn on 18 different LEDs

// Adding SMOOTHING for analog inputs - code is titled smoothingAnalog
// edited code is titled smoothingAnalog4 - rewrote for 4 analog pin reads

// CURRENT STATUS/BUGS: 

// NOTES: 
// --   TESTING AND WORKING
// --   Winning Sequence needs to be determined
// --   Modify MODE - depending on LED or MAGLOCK

// --   FOR IN GAME USE
//      -->  comment out DEBUG


//#define DEBUG 
#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMLEDS 18
#define NUMPIXELS (NUMLEDS*4)

#define RELAY_PIN 3

#define LED_PIN1 6
#define LED_PIN2 7
#define LED_PIN3 8
#define LED_PIN4 10

// -------- FUNCTIONS -----------------
int getVal ( int  );
void displayVal(int  , int );
void checkWin();
void youWIN();
void reset();
//---- Serial Communication ----
char Comp(char* );
void sendData( int  , int  );

// -------- SLIDE POT PINS -----------------

const int slidePin_1 = A0;
const int slidePin_2 = A1;
const int slidePin_3 = A2;
const int slidePin_4 = A3;

// -------- WINNING VALUES -----------------
#define SP1_WIN_VAL 4
#define SP2_WIN_VAL 1
#define SP3_WIN_VAL 2
#define SP4_WIN_VAL 12

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, LED_PIN4, NEO_GRB + NEO_KHZ800);

// -------- DELAY VALUES -----------------
int delayval = 500; // delay for half a second
int readDelay = 5;
int lightDelay = 50;

bool gameWON = false;

// -------- CALIBRATION SETTINGS -----------------
const int calVal_0 = 0;
const int calVal_1 = 2;
const int calVal_2 = 10;
const int calVal_3 = 18;
const int calVal_4 = 31;
const int calVal_5 = 48;
const int calVal_6 = 131;
const int calVal_7 = 238;
const int calVal_8 = 366;
const int calVal_9 = 494;
const int calVal_10 = 620;
const int calVal_11 = 728;
const int calVal_12 = 839;
const int calVal_13 = 960;
const int calVal_14 = 979;
const int calVal_15 = 995;
const int calVal_16 = 1006;
const int calVal_17 = 1013;
const int calVal_18 = 1014;
const int calVal_19 = 1023;

int pot_1_val = 0;
int pot_2_val = 0;
int pot_3_val = 0;
int pot_4_val = 0;


//============================================ SMOOTHING CODE DEFINES - START ====================================================
const int numReadings = 7;

int readings1[numReadings];      // the readings from the analog input
int readings2[numReadings]; 
int readings3[numReadings]; 
int readings4[numReadings]; 

int readIndex1 = 0;              // the index of the current reading
int readIndex2 = 0; 
int readIndex3 = 0; 
int readIndex4 = 0; 

int total1 = 0;                  // the running total
int total2 = 0; 
int total3 = 0; 
int total4 = 0; 

int average1 = 0;                // the average
int average2 = 0;
int average3 = 0;
int average4 = 0;

//---- Serial Communication ----
char inData[20];
char inChar=-1;
byte index = 0;
int incoming_state = 0;
char incoming_char = 0;

bool sendingData = false;
bool fakeReset = false;
bool fakeWin = false;
bool firstLoop = true;

//============================================ SMOOTHING CODE DEFINES - END ======================================================
 
void setup() {
  Serial.begin(9600);
  
  pinMode(slidePin_1, INPUT);
  pinMode(slidePin_2, INPUT);
  pinMode(slidePin_3, INPUT);
  pinMode(slidePin_4, INPUT);

  pinMode(RELAY_PIN, OUTPUT);

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  //pinMode(LED_PIN5, OUTPUT);
  
 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }

  
  //Serial.println("14CORE | Sliding Potensiometer Test Code");
  //Serial.println("========================================");

//============================================ SMOOTHING CODE SETUP - START ==================================================
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
    readings3[thisReading] = 0;
    readings4[thisReading] = 0;
  }
//============================================ SMOOTHING CODE SETUP - END ====================================================

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels1.begin(); // This initializes the NeoPixel library.
  pixels1.show();
  pixels2.begin(); // This initializes the NeoPixel library.
  pixels2.show();
  pixels3.begin(); // This initializes the NeoPixel library.
  pixels3.show();
  pixels4.begin(); // This initializes the NeoPixel library.
  pixels4.show();
  pixels4.begin(); // This initializes the NeoPixel library.
  pixels4.show();
}
 
void loop() {

  // ---- Serial Communication - Phone Win ----
// received a command from the Pi
// FOR SLIDE POTS: incoming date is (1_0 , 1_1 , ..... 4_1, ... 4_18)
// slide topic: phone/pots/slide1 , phone/pots/slide2
// Sending Strings: POT1_0 ... POT4_18

//--------------- SLIDE #1 -----------------------

if(firstLoop){
  Serial.println("SLIDE_RESET");
  firstLoop=false;
}
  
  
  
  
  if (Comp ("potSOLVED") == 0){
    if(!gameWON){  
      fakeWin = true;  
      youWIN();
    }
  }
  
  else if (Comp ("potRESET") == 0){
    if(gameWON){
      fakeReset = true;
      reset();
    }
  }
  else{
    //NULL
  }




  //============================================ SMOOTHING CODE LOOP - START ==================================================
//----------- ANALOG 1 ----------------
  // subtract the last reading:
  total1 = total1 - readings1[readIndex1];
  // read from the sensor:
  readings1[readIndex1] = analogRead(slidePin_1);
  // add the reading to the total:
  total1 = total1 + readings1[readIndex1];
  // advance to the next position in the array:
  readIndex1 = readIndex1 + 1;

  // if we're at the end of the array...
  if (readIndex1 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex1 = 0;
  }

  average1 = total1 / numReadings;
  // send it to the computer as ASCII digits
  #ifdef DEBUG
    Serial.println("Slide Pot 1: ");
  #endif
  pot_1_val = getVal(average1);
  
  sendData(1,pot_1_val);
  
  if(!gameWON){
    displayVal( pot_1_val , 1 );
  }
  delay(readDelay);        // delay in between reads for stability


//----------------------------------------- UNCOMMENTED CODE
//----------- ANALOG 2 ----------------

  total2 = total2 - readings2[readIndex2];
  readings2[readIndex2] = analogRead(slidePin_2);
  total2 = total2 + readings2[readIndex2];
  readIndex2 = readIndex2 + 1;

  if (readIndex2 >= numReadings) {
    readIndex2 = 0;
  }

  average2 = total2 / numReadings;
  //Serial.println(average2);
  #ifdef DEBUG
    Serial.println("Slide Pot 2: ");
  #endif
  pot_2_val = getVal(average2);

  sendData(2,pot_2_val);
  
  if(!gameWON){
    displayVal( pot_2_val , 2 );
  }
  delay(readDelay);        // delay in between reads for stability

  

//----------- ANALOG 3 ----------------

  total3 = total3 - readings3[readIndex3];
  readings3[readIndex3] = analogRead(slidePin_3);
  total3 = total3 + readings3[readIndex3];
  readIndex3 = readIndex3 + 1;

  if (readIndex3 >= numReadings) {
    readIndex3 = 0;
  }

  average3 = total3 / numReadings;
  //Serial.println(average3);
  #ifdef DEBUG
    Serial.println("Slide Pot 3: ");
  #endif
  pot_3_val = getVal(average3);

  sendData(3,pot_3_val);
  
  if(!gameWON){
    displayVal( pot_3_val , 3 );
 }
  delay(readDelay);        // delay in between reads for stability
  

//----------- ANALOG 4 ----------------

  total4 = total4 - readings4[readIndex4];
  readings4[readIndex4] = analogRead(slidePin_4);
  total4 = total4 + readings4[readIndex4];
  readIndex4 = readIndex4 + 1;

  if (readIndex4 >= numReadings) {
    readIndex4 = 0;
  }

  average4 = total4 / numReadings;
  //Serial.println(average4);
  #ifdef DEBUG
    Serial.println("Slide Pot 4: ");
  #endif
  pot_4_val = getVal(average4);

  sendData(4,pot_4_val);
  
  if(!gameWON){
    displayVal( pot_4_val , 4 );
  }
  delay(readDelay);        // delay in between reads for stability
  //Serial.println();


//============================================ SMOOTHING CODE LOOP - END  ===================================================


  checkWin();

}

//=============================================== FUNCTIONS ======================================================


//------------------------------------- GET READINGS -----------------------------------------------
// takes in average value of slide pot and returns value for LEDs ( 0 - NUMLEDS )

int getVal ( int _potVal ){

  if(_potVal>=calVal_0 && _potVal<calVal_1){
    #ifdef DEBUG
       Serial.println(" Calibration 0 ");
    #endif
    return 0;
  }
  else if(_potVal>=calVal_1 && _potVal<calVal_2){
    #ifdef DEBUG
       Serial.println(" Calibration 1 ");
    #endif
    return 1;
  }
  else if(_potVal>=calVal_2 && _potVal<calVal_3){
    #ifdef DEBUG
       Serial.println(" Calibration 2 ");
    #endif
    return 2;
  }
  else if(_potVal>=calVal_3 && _potVal<calVal_4){
    #ifdef DEBUG
       Serial.println(" Calibration 3 ");
    #endif
    return 3;
  }
  else if(_potVal>=calVal_4 && _potVal<calVal_5){
    #ifdef DEBUG
       Serial.println(" Calibration 4 ");
    #endif
    return 4;
  }  
  else if(_potVal>=calVal_5 && _potVal<calVal_6){
    #ifdef DEBUG
       Serial.println(" Calibration 5 ");
    #endif
    return 5;
  }
  else if(_potVal>=calVal_6 && _potVal<calVal_7){
    #ifdef DEBUG
       Serial.println(" Calibration 6 ");
    #endif
    return 6;
  }
  else if(_potVal>=calVal_7 && _potVal<calVal_8){
    #ifdef DEBUG
       Serial.println(" Calibration 7 ");
    #endif
    return 7;
  }
  else if(_potVal>=calVal_8 && _potVal<calVal_9){
    #ifdef DEBUG
       Serial.println(" Calibration 8 ");
    #endif
    return 8;
  }
  else if(_potVal>=calVal_9 && _potVal<calVal_10){
    #ifdef DEBUG
       Serial.println(" Calibration 9 ");
    #endif
    return 9;
  }  
  else if(_potVal>=calVal_10 && _potVal<calVal_11){
    #ifdef DEBUG
       Serial.println(" Calibration 10 ");
    #endif
    return 10;
  }
  else if(_potVal>=calVal_11 && _potVal<calVal_12){
    #ifdef DEBUG
       Serial.println(" Calibration 11 ");
    #endif
    return 11;
  }
  else if(_potVal>=calVal_12 && _potVal<calVal_13){
    #ifdef DEBUG
       Serial.println(" Calibration 12 ");
    #endif
    return 12;
  }
  else if(_potVal>=calVal_13 && _potVal<calVal_14){
    #ifdef DEBUG
       Serial.println(" Calibration 13 ");
    #endif
    return 13;
  }
  else if(_potVal>=calVal_14 && _potVal<calVal_15){
    #ifdef DEBUG
       Serial.println(" Calibration 14 ");
    #endif
    return 14;
  }
  else if(_potVal>=calVal_15 && _potVal<calVal_16){
    #ifdef DEBUG
       Serial.println(" Calibration 15 ");
    #endif
    return 15;
  }
  else if(_potVal>=calVal_16 && _potVal<calVal_17){
    #ifdef DEBUG
       Serial.println(" Calibration 16 ");
    #endif
    return 16;
  }  
  else if(_potVal>=calVal_17 && _potVal<calVal_18){
    #ifdef DEBUG
       Serial.println(" Calibration 17 ");
    #endif
    return 17;
  }
  else if(_potVal>=calVal_18 && _potVal<=calVal_19){
    #ifdef DEBUG
       Serial.println(" Calibration 18 ");
    #endif
    return 18;
  }
  else return 18;
  
}


//------------------------------------- GET READINGS -----------------------------------------------
// takes in LED value and slide pot number ( 0 to 4 ) to display Leds --> displays to LEDs
// _slideNum : 0 - reserved for clearing all LEDs
// _slideNum : 5 - reserved for WINNING SEQUENCE

void displayVal(int _tempVal , int _slideNum){

  int onVal = 0; // max led on number calculated for each slide pot

  switch(_slideNum){
    
    case 0:
    break;
    
    case 1:
      onVal = _tempVal;
      
      for( int i=0; i < onVal; i++){
        pixels1.setPixelColor(i, pixels1.Color(0,150,0)); // Moderately bright green color.
      }
      for( int i=onVal; i <= 17; i++){
        pixels1.setPixelColor(i, pixels1.Color(0,0,0)); 
      }
    break;

    case 2:
      onVal =  _tempVal;

      for( int i=0; i < onVal; i++){
        pixels2.setPixelColor(i, pixels2.Color(150,0,0)); // Moderately bright red color.
      }
      for( int i=onVal; i <= 17; i++){
        pixels2.setPixelColor(i, pixels2.Color(0,0,0)); 
      }
    break;

    case 3:
      onVal =  _tempVal;

      for( int i=0; i < onVal; i++){
        pixels3.setPixelColor(i, pixels3.Color(0,0,150)); // Moderately bright blue color.
      }
      for( int i=onVal; i <= 17; i++){
        pixels3.setPixelColor(i, pixels3.Color(0,0,0)); 
      }
    break;

    case 4:
      onVal = _tempVal;

      for( int i=0; i < onVal; i++){
        pixels4.setPixelColor(i, pixels4.Color(150,0,150)); // Moderately bright purple color.
      }
      for( int i=onVal; i <= 17; i++){
        pixels4.setPixelColor(i, pixels4.Color(0,0,0)); 
      }
    break;

    case 5:
    break;

    default:
    break;
  }
      delay(1);
      pixels1.show(); // This sends the updated pixel color to the hardware.
      pixels2.show();
      pixels3.show();
      pixels4.show();

  
}

//------------------------------------- CHECK WIN -----------------------------------------------
// takes in LED value and slide pot number ( 0 to 4 ) to display Leds --> displays to LEDs
void checkWin(){

if(!gameWON){
  if ( pot_1_val == SP1_WIN_VAL ){
    if ( pot_2_val == SP2_WIN_VAL ){
      if ( pot_3_val == SP3_WIN_VAL ){
        if ( pot_4_val == SP4_WIN_VAL ){
          // YOU WIN!!!
          //gameWON = true;
          youWIN();
        }
      }
    }
  }
}
else if(gameWON){
  
  if ( pot_1_val == 18 ){
    if ( pot_2_val == 18 ){
      if ( pot_3_val == 7 ){
        //Serial.println("Check for Reset");
        if ( pot_4_val == 18 ){
          // RESET PUZZLE
          reset();
        }
      }
    }
  }  
}
//else Serial.println("GAME WON ERROR");;
  
}

//------------------------------------- YOU WON -----------------------------------------------
// WINNING SEQUENCE
void youWIN(){

//Serial.println("WINNING CYCLE");

if(!fakeWin){
  Serial.println("SLIDE_WIN");}

  for( int i=0; i <= 17; i++){
    pixels1.setPixelColor(i, 0,0,0); 
    pixels2.setPixelColor(i, 0,0,0); 
    pixels3.setPixelColor(i, 0,0,0); 
    pixels4.setPixelColor(i, 0,0,0);
  }
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(lightDelay);

   for( int i=0; i <= 17; i++){
     pixels1.setPixelColor(i, 0,(i*11)+11,0); 
     pixels2.setPixelColor(i, (i*11)+11,0,0); 
     pixels3.setPixelColor(i, 0,0,(i*11)+11); 
     pixels4.setPixelColor(i,(i*11)+11,0,(i*11)+11);
     pixels1.show(); // This sends the updated pixel color to the hardware.
     pixels2.show();
     pixels3.show();
     pixels4.show();
     delay(lightDelay);
   }

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, LOW);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, HIGH);  
 }

  gameWON = true;
  fakeWin = false;

}


//------------------------------------- RESET GAME -----------------------------------------------
// reset the game and all variables for the next game
void reset(){
  //Serial.println("RESET CYCLE");
  if(!fakeReset){
    Serial.println("SLIDE_RESET");}

 displayVal( 0 , 1 ); 
 displayVal( 0 , 2 );
 displayVal( 0 , 3 );
 displayVal( 0 , 4 );
 
 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }
  gameWON = false;
  fakeReset = false;
}

// Send data to Pi for MQTT
void sendData( int potNum , int val ){
  
  if (sendingData){

  if ( potNum == 1 ){
    if ( val == 0 ) Serial.println("POT1_0");
    else if ( val == 1 ) Serial.println("POT1_1");
    else if ( val == 2 ) Serial.println("POT1_2");
    else if ( val == 3 ) Serial.println("POT1_3");
    else if ( val == 4 ) Serial.println("POT1_4");
    else if ( val == 5 ) Serial.println("POT1_5");
    else if ( val == 6 ) Serial.println("POT1_6");
    else if ( val == 7 ) Serial.println("POT1_7");
    else if ( val == 8 ) Serial.println("POT1_8");
    else if ( val == 9 ) Serial.println("POT1_9");
    else if ( val == 10 ) Serial.println("POT1_10");
    else if ( val == 11 ) Serial.println("POT1_11");
    else if ( val == 12 ) Serial.println("POT1_12");
    else if ( val == 13 ) Serial.println("POT1_13");
    else if ( val == 14 ) Serial.println("POT1_14");
    else if ( val == 15 ) Serial.println("POT1_15");
    else if ( val == 16 ) Serial.println("POT1_16");
    else if ( val == 17 ) Serial.println("POT1_17");
    else if ( val == 18 ) Serial.println("POT1_18");
    
  }

  else if ( potNum == 2 ){
    if ( val == 0 ) Serial.println("POT2_0");
    else if ( val == 1 ) Serial.println("POT2_1");
    else if ( val == 2 ) Serial.println("POT2_2");
    else if ( val == 3 ) Serial.println("POT2_3");
    else if ( val == 4 ) Serial.println("POT2_4");
    else if ( val == 5 ) Serial.println("POT2_5");
    else if ( val == 6 ) Serial.println("POT2_6");
    else if ( val == 7 ) Serial.println("POT2_7");
    else if ( val == 8 ) Serial.println("POT2_8");
    else if ( val == 9 ) Serial.println("POT2_9");
    else if ( val == 10 ) Serial.println("POT2_10");
    else if ( val == 11 ) Serial.println("POT2_11");
    else if ( val == 12 ) Serial.println("POT2_12");
    else if ( val == 13 ) Serial.println("POT2_13");
    else if ( val == 14 ) Serial.println("POT2_14");
    else if ( val == 15 ) Serial.println("POT2_15");
    else if ( val == 16 ) Serial.println("POT2_16");
    else if ( val == 17 ) Serial.println("POT2_17");
    else if ( val == 18 ) Serial.println("POT2_18");
  }

  else if ( potNum == 3 ){
    if ( val == 0 ) Serial.println("POT3_0");
    else if ( val == 1 ) Serial.println("POT3_1");
    else if ( val == 2 ) Serial.println("POT3_2");
    else if ( val == 3 ) Serial.println("POT3_3");
    else if ( val == 4 ) Serial.println("POT3_4");
    else if ( val == 5 ) Serial.println("POT3_5");
    else if ( val == 6 ) Serial.println("POT3_6");
    else if ( val == 7 ) Serial.println("POT3_7");
    else if ( val == 8 ) Serial.println("POT3_8");
    else if ( val == 9 ) Serial.println("POT3_9");
    else if ( val == 10 ) Serial.println("POT3_10");
    else if ( val == 11 ) Serial.println("POT3_11");
    else if ( val == 12 ) Serial.println("POT3_12");
    else if ( val == 13 ) Serial.println("POT3_13");
    else if ( val == 14 ) Serial.println("POT3_14");
    else if ( val == 15 ) Serial.println("POT3_15");
    else if ( val == 16 ) Serial.println("POT3_16");
    else if ( val == 17 ) Serial.println("POT3_17");
    else if ( val == 18 ) Serial.println("POT3_18");
  }

  else if ( potNum == 4 ){
    if ( val == 0 ) Serial.println("POT4_0");
    else if ( val == 1 ) Serial.println("POT4_1");
    else if ( val == 2 ) Serial.println("POT4_2");
    else if ( val == 3 ) Serial.println("POT4_3");
    else if ( val == 4 ) Serial.println("POT4_4");
    else if ( val == 5 ) Serial.println("POT4_5");
    else if ( val == 6 ) Serial.println("POT4_6");
    else if ( val == 7 ) Serial.println("POT4_7");
    else if ( val == 8 ) Serial.println("POT4_8");
    else if ( val == 9 ) Serial.println("POT4_9");
    else if ( val == 10 ) Serial.println("POT4_10");
    else if ( val == 11 ) Serial.println("POT4_11");
    else if ( val == 12 ) Serial.println("POT4_12");
    else if ( val == 13 ) Serial.println("POT4_13");
    else if ( val == 14 ) Serial.println("POT4_14");
    else if ( val == 15 ) Serial.println("POT4_15");
    else if ( val == 16 ) Serial.println("POT4_16");
    else if ( val == 17 ) Serial.println("POT4_17");
    else if ( val == 18 ) Serial.println("POT4_18");
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
