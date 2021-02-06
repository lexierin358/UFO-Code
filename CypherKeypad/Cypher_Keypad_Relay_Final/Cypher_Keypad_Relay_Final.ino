// PUZZLE: Sound Card Inserts

// DATE CREATED: 6/29/18
// LAST DATE EDITED: 8/29/20

// FINAL CODE: code updated for the game play

// PREVIOUS CODE : Alien Keypad

// NOTES:
// NOTES: Attempting on NANO - 7/2/18

// PROJECT: SAMPLE CODE TO USE FOR ALL BUTTONS
// CURRENT STATUS/BUGS: UNTESTED WITH BUTTONS
// NOTES: this code is for alien keypad, only keeping track of last 4 buttons pressed
//  and sequence.



//----------- DEFINES -------------------------------------------------------------

#define numButtons 10

#define ButtonPin_1 11
#define ButtonPin_2 2
#define ButtonPin_3 3
#define ButtonPin_4 4
#define ButtonPin_5 5
#define ButtonPin_6 6
#define ButtonPin_7 7
#define ButtonPin_8 8
#define ButtonPin_9 9
#define ButtonPin_10 10

#define RelayPin 12

#define pLeng 4 // Password Length

//----------- FUNCTIONS -------------------------------------------------------------

void getInput(int );  // Gets user inputs
void updateUserCode(int ); // Only keeping track of the last 4 buttons presses
bool checkPassword(); // Returns True if Correct & False if Incorrect
void winningSequence(); // What happens when you winner!!
void printUserCode();


void resetSequence();
bool checkReset();

//void storeNum(int );  // Saves user inputs & updates counter "currPosition" - Not Used

//----------- VARIABLES -------------------------------------------------------------

unsigned long debounceDelay = 50; // Increase is there is to much noise
unsigned long lastDebounceTime = 0;

int lasttouched = 0;
int currtouched = 0;

int bufferVal[numButtons];
int buttonState[numButtons];
int lastState[numButtons];
//int lastDebounceTimer[numButtons];

int userCode[pLeng];
//int password_1[pLeng] = { 5 , 2 , 6 , 8 }; // 6 3 7 10

int password_1[pLeng] = { 7 , 5 , 1 , 9 };
bool passwordCorrect = false; // Password Flag - True if password is correct, else False
bool gameWon = false;
//int currPosition = 0;

//=========================== SETUP ==========================================================
void setup() {

  Serial.begin(9600);

  for(int i=0 ; i<pLeng ; i++){
    userCode[i]=0;
  }

//----------- PIN MODES -------------------------------------------------------------
  
  pinMode(ButtonPin_1,INPUT_PULLUP);
  pinMode(ButtonPin_2,INPUT_PULLUP);
  pinMode(ButtonPin_3,INPUT_PULLUP);
  pinMode(ButtonPin_4,INPUT_PULLUP);
  pinMode(ButtonPin_5,INPUT_PULLUP);
  pinMode(ButtonPin_6,INPUT_PULLUP);
  pinMode(ButtonPin_7,INPUT_PULLUP);
  pinMode(ButtonPin_8,INPUT_PULLUP);
  pinMode(ButtonPin_9,INPUT_PULLUP);
  pinMode(ButtonPin_10,INPUT_PULLUP);
  pinMode(RelayPin,OUTPUT);

  digitalWrite(RelayPin,HIGH);
  Serial.println("RELAY CLOSED ");

}


//=========================== MAIN LOOP ======================================================
void loop() {

bufferVal[0] = digitalRead(ButtonPin_1);
bufferVal[1] = digitalRead(ButtonPin_2);
bufferVal[2] = digitalRead(ButtonPin_3);
bufferVal[3] = digitalRead(ButtonPin_4);
bufferVal[4] = digitalRead(ButtonPin_5);
bufferVal[5] = digitalRead(ButtonPin_6);
bufferVal[6] = digitalRead(ButtonPin_7);
bufferVal[7] = digitalRead(ButtonPin_8);
bufferVal[8] = digitalRead(ButtonPin_9);
bufferVal[9] = digitalRead(ButtonPin_10);
  
  

  
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
        
        if (buttonState[i] == LOW){ // If  the button is Pressed          
          getInput(i);
         //Serial.print("Button Pressed: ");
          //Serial.println(i);
          }
      }
    }
    lastState[i] = bufferVal[i]; // Save values for next loop
  }
}


//=========================== FUNCTIONS ======================================================

//----------- WINNING SEQUENCE -----------------------------------------------
void printUserCode(){

  Serial.print("User Code:  ");
  for(int i=0; i<pLeng; i++){
    Serial.print(userCode[i]);
    Serial.print("  ");
  }

  Serial.println();
}
//----------- WINNING SEQUENCE -----------------------------------------------
void winningSequence(){
  
  passwordCorrect = false; //reset passCorrect for next time around
  gameWon = true;
  digitalWrite(RelayPin, LOW);
  Serial.println("RELAY OPEN");
  Serial.println("WINNER WINNER CHICKEN DINNER!!!");
  
}

//----------- CHECK USER PASSWORD -----------------------------------------------
bool checkPassword(){
  // If any value doesn't match password stop and return 0, else return 1

  Serial.println("Check Password");
  printUserCode();

  for( int i=0 ; i<pLeng ; i++){
    if(userCode[i] != password_1[i]){
      Serial.print("Incorrect at :");
      Serial.println(i);
      return false;}  
    }
  return true;
}

//----------- UPDATE USER CODE -----------------------------------------------
void updateUserCode(int _currButton ){

  Serial.print("Update User Code: ");
  Serial.println(_currButton);
  
  
 //update user code - only keeping track of last 4 buttons presses
  for( int i=0 ; i<pLeng-1 ; i++){
    userCode[i] = userCode[i+1];}     
  userCode[pLeng-1] = _currButton;

  passwordCorrect = checkPassword(); // User Code changed - Check Password

  // --------------WINNING SEQUENCE--------------------
  if(passwordCorrect && !gameWon) {
    winningSequence();
  }
  else if(passwordCorrect && gameWon){
    resetSequence();
  }
  
}

//----------- GET INPUT -----------------------------------------------
void getInput(int _input){
  
  switch ( _input){
    case 0: updateUserCode(_input);
      Serial.println('1');
      break;
    case 1: updateUserCode(_input);
      Serial.println('2');
      break;
    case 2: updateUserCode(_input);
      Serial.println('3');
      break;
    case 3: updateUserCode(_input);
      Serial.println('4');
      break;
    case 4: updateUserCode(_input);
      Serial.println('5');
      break;
    case 5: updateUserCode(_input);
      Serial.println('6');
      break;
    case 6: updateUserCode(_input);
      Serial.println('7');
      break;
    case 7: updateUserCode(_input);
      Serial.println('8');
      break;
    case 8: updateUserCode(_input);
      Serial.println('9');
      break;
    case 9: updateUserCode(_input);
      Serial.println("10");
      break;
    case 10: updateUserCode(_input);
      break;
    default: // DO NOTHING
      break;
  }
}

bool checkReset(){    // probaly not needed  
    if(gameWon){
      for( int i=0 ; i<pLeng ; i++){
        if(userCode[i] != password_1[i]){
          Serial.print("Incorrect RESET at :");
          Serial.println(i);
          return false;}  
        }
      return true;  
    }
    return false;
}

void resetSequence(){
  //reset game
  passwordCorrect = false; //reset passCorrect for next time around
  gameWon = false;
  digitalWrite(RelayPin, HIGH);
  Serial.println("RELAY CLOSED");
}




/*
//----------- STORE INPUT -----------------------------------------------

void storeNum(int _currNum ){
  // currNum : the actual button being pressed
  // currPos : the number of sequential inputs

  userCode[currPosition] = _currNum; // Store user input
  tempPosition++; // update tempPosition for next line
  currPosition = tempPosition%pLeng; // 

  //printUserCode();
}
*/





//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
//----------- FUNCTION NAME -----------------------------------------------
