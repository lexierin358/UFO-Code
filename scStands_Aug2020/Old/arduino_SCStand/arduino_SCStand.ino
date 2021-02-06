// PUZZLE: Sound Card Inserts

// DATE CREATED: 10/11/18
// LAST DATE EDITED: 1/20/19

// PREVIOUS CODE : Alien Keypad

// NOTES: NEW SOUND CARD CODE 
// Serial communication and MQTT code added 

// NOTES: 12/14/18 - Tested Sound Card Boxes
//                    - 2 Card Slots are wired wrong


#include <Wire.h>
//----------- DEFINES -------------------------------------------------------------
//#define DEBUG

#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 

#define numButtons 10
#define numSounds 5

#define ButtonPin_1 6
#define ButtonPin_2 5
#define ButtonPin_3 4
#define ButtonPin_4 3
#define ButtonPin_5 2

#define SoundPin_1 7
#define SoundPin_2 8
#define SoundPin_3 9
#define SoundPin_4 10
#define SoundPin_5 11


//#define ButtonPin_6 6
//#define ButtonPin_7 7
//#define ButtonPin_8 8
//#define ButtonPin_9 9
//#define ButtonPin_10 10

#define RELAY_PIN 12


//----------- FUNCTIONS -------------------------------------------------------------

void cardInserted(int );   
void cardRemoved(int );    
void checkWin ();  
void checkReset();
char Comp(char* );


void youWIN(); // What happens when you winner!!
void reset();


//----------- VARIABLES -------------------------------------------------------------

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

int cardFlag1 = 0, cardFlag2 = 0, cardFlag3 = 0, cardFlag4 = 0, cardFlag5 = 0;    // not needed
//int cardFlag6 = 0, cardFlag7 = 0, cardFlag8 = 0, cardFlag9 = 0, cardFlag10 = 0;    // not needed
int cardFLAG = 0;    // not needed
//int winFLAG = 0;     // not needed

unsigned long debounceDelay = 50; // Increase is there is to much noise
unsigned long lastDebounceTime = 0;

int lasttouched = 0;
int currtouched = 0;

int bufferVal[numButtons];
int buttonState[numButtons];
int lastState[numButtons];

bool winFLAG = false;   // not needed
bool winner = false;    // not needed

bool emptySlot = false;

bool gameWON  = false;
bool gameReset = false;

int incoming_state = 0;  //Initializes a variable for storing the incoming data from Arduino
char incoming_char;


//=========================== SETUP ==========================================================
void setup() {

  Serial.begin(9600);
  #ifdef DEBUG
  Serial.println("Sound Card Testing");
  Serial.println("-------------------------");
  #endif
  
  Serial.println("START");
  
  int LED_BUILTIN = 13;
  digitalWrite(LED_BUILTIN, LOW);
  


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
  
  pinMode(LED_BUILTIN,OUTPUT);
  
  pinMode(SoundPin_1,INPUT);
  pinMode(SoundPin_2,INPUT);
  pinMode(SoundPin_3,INPUT);
  pinMode(SoundPin_4,INPUT);
  pinMode(SoundPin_5,INPUT);

digitalWrite(LED_BUILTIN,HIGH);

}


//=========================== MAIN LOOP ======================================================
void loop() {

bufferVal[0] = digitalRead(ButtonPin_1);
bufferVal[1] = digitalRead(ButtonPin_2);
bufferVal[2] = digitalRead(ButtonPin_3);
bufferVal[3] = digitalRead(ButtonPin_4);
bufferVal[4] = digitalRead(ButtonPin_5);

bufferVal[5] = digitalRead(SoundPin_1);
bufferVal[6] = digitalRead(SoundPin_2);
bufferVal[7] = digitalRead(SoundPin_3);
bufferVal[8] = digitalRead(SoundPin_4);
bufferVal[9] = digitalRead(SoundPin_5);
  
  
// Start out believing all cards are correct " emptySlot = false "
//    ONLY CHECKING FOR EMPTY SLOT -> IF NONE -> YOU WIN!
//    if any slot is empty " emptySlot = true "

//    int incomingByte;
//    
//    if(Serial.available() > 0) {
//      // read the incoming byte:
//      incomingByte = Serial.read();
//  
//      // echo
//      Serial.println("arduino recieved message a");
//      Serial.write(incomingByte); 
//  }


// --------------------------- RECIEVED COMMAND FROM PI -> PHONE -----------------------------------
// -----------------CARD # 1 ---------------------
    if (Comp("1in")==0) {
        Serial.println("1 INSERTED");
        cardFlag1=1;
    }
    else if (Comp("1out")==0) {
        Serial.println("1 REMOVED");
        cardFlag1=0;
    }
    
// -----------------CARD # 2 ---------------------  
    else if (Comp("2in")==0) {
        //Serial.println("1 INSERTED");
        cardFlag2=1;
    }
    else if (Comp("2out")==0) {
        //Serial.println("1 REMOVED");
        cardFlag2=0;
    }
    
// -----------------CARD # 3 ---------------------
    else if (Comp("3in")==0) {
        //Serial.println("1 INSERTED");
        cardFlag3=1;
    }
    
    else if (Comp("3out")==0) {
        //Serial.println("1 REMOVED");
        cardFlag3=0;
    }
    
// -----------------CARD # 4 ---------------------
    else if (Comp("4in")==0) {
        //Serial.println("1 INSERTED");
        cardFlag4=1;
    }
    
    else if (Comp("4out")==0) {
        //Serial.println("1 REMOVED");
        cardFlag4=0;
    }
    
// -----------------CARD # 5 ---------------------
    else if (Comp("5in")==0) {
        //Serial.println("1 INSERTED");
        cardFlag5=1;
    }
    
    else if (Comp("5out")==0) {
        //Serial.println("1 REMOVED");
        cardFlag5=0;
    }

    else{
      //Serial.println("NULL");
      
    }
//
//  if (Serial.available() > 0){  //Looking for incoming data
//    incoming_state = Serial.read() - '0';  //Reading the data
//    //incoming_char = Serial.read() - '0';
//    //digitalWrite(LED_BUILTIN, incoming_state);  //Making the LED light up or down
//
//    if (      incoming_state == 0){ 
//      Serial.println('Z');
//      cardFlag1=0;
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 1){ 
//      cardFlag1=1;
//      //Serial.println('z');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 2){ 
//      cardFlag2=0;
//      //Serial.println('T');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 3){ 
//      cardFlag2=1;
//      //Serial.println('t');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 4){ 
//      cardFlag3=0;
//      //Serial.println('z');
//      digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 5){ 
//      cardFlag3=1;
//      //Serial.println('T');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 6){ 
//      cardFlag4=0;
//      //Serial.println('t');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 7){ 
//      cardFlag4=1;
//      //Serial.println('z');
//      digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 8){ 
//      cardFlag5=0;
//      //Serial.println('T');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else if ( incoming_state == 9){ 
//      cardFlag5=1;
//      //Serial.println('t');
//      //digitalWrite(LED_BUILTIN, incoming_state);
//    }
//    else{
//      //Serial.println("NULL");
//    }
//    else if ( incoming_char == 'Z'){
//      Serial.println('Z');
//    }
//  }
  
  //button_state = digitalRead(button_pin); //Reading the button state
  //Serial.println(incoming_state);  //Sending the data over serial to Raspberry pi
  
  
  
  

emptySlot = false;
  
    for( int i=0 ; i<numButtons ; i++ ){  
  
        if ( bufferVal[i] != lastState[i]){ // Switch changed, due to noise or press
          lastDebounceTime = millis();
        }
        
        if((millis() - lastDebounceTime) > debounceDelay){ // Change has been longer that debounce delay
         
            if (bufferVal[i] != buttonState[i]){ // If the button state changed
              buttonState[i] = bufferVal[i]; // Take the bufferVal as new State
              //Serial.print(" Button State is officaially changed ");
              
                if (buttonState[i] == HIGH){ // If  the button is Pressed  
                  // ONLY USED FOR TESTING ------------------- //cardInserted(i);        
                  cardInserted(i);
                  }
                else {
                  emptySlot = true;
                  //gameWON = false;
                  // ONLY USED FOR TESTING ------------------- //cardRemoved();
                  cardRemoved(i);
                  }  
            }
        }
      lastState[i] = bufferVal[i]; // Save values for next loop
    }
    
    


  
  checkWin();
  checkReset();
  
  //if(gameWON == true){
    //Serial.println("check Reset");
   // checkReset();
 // }

// if there are no empty slots and the game isn't won yet -> youWIN
  if ( (!emptySlot) && (!gameWON) ){
    //Serial.println("No Empty Slots and Game Not Won");
    //youWIN();    
  }

// if you are ready won and now there are empty slots -> reset the game
  if( gameWON && emptySlot){
    //Serial.println("resetting");
    //reset();
  }
  
}


//=========================== FUNCTIONS ======================================================
// ---------- COMPARE INCOMING STRING FROM SERIAL ---------------------------
// EXAMPLE:  if (Comp("1on")==0) 

char Comp(char* This) {
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}


//----------- WINNING SEQUENCE -----------------------------------------------
void youWIN(){
#ifdef DEBUG
Serial.println("YOU WON");
#endif

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, LOW);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 
  winner = true;
  
  gameWON = true;
  Serial.println("SC_1_SOLVED");
  //Serial.println('w');
  //winFLAG = true;
  //Serial.println("WINNER WINNER CHICKEN DINNER!!!");
  
}

//----------- RESET THE GAME -----------------------------------------------
void reset(){
#ifdef DEBUG
Serial.println("RESET GAME");
#endif

//Serial.println('r');

 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);   
 }
 
 gameWON = false;
 Serial.println("SC_1_RESET");
      
  
}

//----------- CHECK USER PASSWORD -----------------------------------------------
void checkWin(){
  // If any value doesn't match password stop and return 0, else return 1
  if(gameWON == false){
  if ( cardFlag1 == 1 ){
    if ( cardFlag2 == 1){
      if ( cardFlag3 == 1){
        if ( cardFlag4 == 1){
          if ( cardFlag5 == 1){
            //Serial.println("card Flag WINNER!");
            //Serial.println("
                      //winFLAG = 1;
                      //youWIN();
                      //return true;
                      //Serial.println("WIN");
                      youWIN();
                      //gameWON = true;
                      
                    }
                  }
                }
                
              }
            }

  

else {
  //winFLAG = false;
 // return false;
}
  }
}

//----------- CHECK USER PASSWORD -----------------------------------------------
void checkReset(){
 
  // If any value doesn't match password stop and return 0, else return 1
 if(gameWON == true){
   
  if ( cardFlag1 == 0 ){
    //Serial.println('z');
    if ( cardFlag2 == 0){
      
      if ( cardFlag3 == 0){
        
        if ( cardFlag4 == 0){
           
          if ( cardFlag5 == 0){
            //Serial.println("card Flag Reset!");
                      //winFLAG = 1;
                      //youWIN();
                      //return true;
                      //Serial.println('r');
                      reset();
                      //gameWON = false;
                      
                    }
                  }
                }
                
              }
            }
 }

  

else {
  //winFLAG = false;
 // return false;
}
  //}
}


//----------- CARD INSERTED -----------------------------------------------
void cardInserted(int _input){
  
  switch ( _input){
    case 0: cardFlag1 = 1;
      Serial.println("1_INSERTED");
      //Serial.println("Card 1 Inserted");
      break;
    case 1: 
      cardFlag2 = 1;
      Serial.println("2_INSERTED");
      //Serial.println('B');
      //Serial.println("Card 2 Inserted");
      break;
    case 2: cardFlag3 = 1;
      Serial.println("3_INSERTED");
      //Serial.println('C');
      //Serial.println("Card 3 Inserted");
      break;
    case 3: cardFlag4 = 1;
      Serial.println("4_INSERTED");
      //Serial.println('D');
      //Serial.println("Card 4 Inserted");
      break;
    case 4: cardFlag5 = 1;
      Serial.println("5_INSERTED");
      //Serial.println('E');
      //Serial.println("Card 5 Inserted");
      break;
      
    case 5:
      Serial.println("SOUND_1");
      //Serial.println('E');
      //Serial.println("Card 5 Inserted");
      break;
    case 6: 
      Serial.println("SOUND_2");
      //Serial.println('B');
      //Serial.println("Card 2 Inserted");
      break;
    case 7:
      Serial.println("SOUND_3");
      //Serial.println('C');
      //Serial.println("Card 3 Inserted");
      break;
    case 8: 
      Serial.println("SOUND_4");
      //Serial.println('D');
      //Serial.println("Card 4 Inserted");
      break;
    case 9: 
      Serial.println("SOUND_5");
      //Serial.println('E');
      //Serial.println("Card 5 Inserted");
      break;

    case 10: //updateUserCode(_input);
      break;
    default: // DO NOTHING
      break;
  }
  //checkWin();
}

//----------- CARD REMOVED -----------------------------------------------
void cardRemoved(int _input){

  //emptySlot = true;
  
  switch ( _input){
    case 0: cardFlag1 = 0;
      Serial.println("1_REMOVED");
      //Serial.println("Card 1 Removed");
      break;
    case 1: cardFlag2 = 0;
      Serial.println("2_REMOVED");
      //Serial.println('b');
      //Serial.println("Card 2 Removed");
      break;
    case 2: cardFlag3 = 0;
      Serial.println("3_REMOVED");
      //Serial.println('f');
      //Serial.println("Card 3 Removed");
      break;
    case 3: cardFlag4 = 0;
      Serial.println("4_REMOVED");
      //Serial.println('d');
      //Serial.println("Card 4 Removed");
      break;
    case 4: cardFlag5 = 0;
      Serial.println("5_REMOVED");
      //Serial.println('e');
      //Serial.println("Card 5 Removed");
      break;

    case 10: //updateUserCode(_input);
      break;
    default: // DO NOTHING
      break;
  }
}

//----------- DEBUG PRINT -----------------------------------------------

//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------








