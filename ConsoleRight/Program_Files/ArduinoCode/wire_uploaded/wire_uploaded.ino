// THIS IS THE CODE I AM WORKING ON

// DATE CREATED: 7/3/18
// LAST DATE EDITED: 5/24/19

// FINAL VERSION COLORED WIRE WITH MQTT ***

// PROJECT: Analog Read - Wire Puzzle
// CURRENT STATUS/BUGS: 
// NOTES: 

/*

  RESISTOR VALUES:
    1K: 930
    4.7K: 697
    22K: 318
    100K: 90
    5 volt: 1023
 
 */


//----------- DEFINES -------------------------------------------------------------

#define MAGLOCK 1
#define LEDLIGHT 0
// set the mode here
#define MODE MAGLOCK 

// ==== DEFINE PINS WITH ANOALOG (A) NOT PIN # ===

#define Pin1 A0
#define Pin2 A1
#define Pin3 A2
#define Pin4 A3
#define Pin5 A4
#define Pin6 A5

#define RELAY_PIN 7

#define TEST_PIN 8



// A0 -  97
// A1 -  96
// A2 -  95
// A3 -  94
// A4 -  93
// A5 -  92
// A6 -  91
// A7 -  90
// A8 -  89
// A9 -  88
// A10 - 87
// A11 - 86
// A12 - 85
// A13 - 84
// A14 - 83
// A15 - 82

  // ANALOG PINS 14 to 19 : Maybe A0 to A5

  // ARDUINO MEGA ANALOG PINS 82 (A15) TO 97 (A0)

//----------- FUNCTIONS -----------------------------------------------------------

void youWIN();

char Comp(char* );

void reset();

//---- Serial Communication ----
char inData[20];
char inChar=-1;
byte index = 0;
int incoming_state = 0;
char incoming_char = 0;

//void getFunctions(int );  // Gets Functions

//----------- VARIABLES -----------------------------------------------------------
int fakeWin_Delay = 3000; //amount of time you want Mag Lock unlocked for -> for a fake win
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;

int flagCount = 0;
bool winFlag = false;

bool fakeReset = false;
bool fakeWin = false;

bool gameWON = false;

int checkEmpty = 0;
int emptyCount = 0;

bool firstLoop = true;


//=========================== SETUP =========================================================
void setup() {

  Serial.begin(9600);
  pinMode(Pin1,INPUT);
  pinMode(Pin2,INPUT);
  pinMode(Pin3,INPUT);
  pinMode(Pin4,INPUT);
  pinMode(Pin5,INPUT);
  
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(TEST_PIN,OUTPUT);
  
  //Serial.println("WIRE_RESET");
  
 if (MODE == MAGLOCK){
  digitalWrite(RELAY_PIN, HIGH);  
 }
 if (MODE == LEDLIGHT){
  digitalWrite(RELAY_PIN, LOW);  
 }
 digitalWrite(TEST_PIN,LOW);
  

}

//=========================== MAIN LOOP ======================================================
void loop() {

  if( firstLoop){
    delay(2000);
    Serial.println("WIRE_RESET");    
    firstLoop = false;
    }
  
   if (Comp ("wireSOLVED") == 0){
    if(!gameWON){  
 
       digitalWrite(TEST_PIN,HIGH);       
       delay(fakeWin_Delay);
       
      fakeWin = true;  
      youWIN();
    }
  }
  
  else if (Comp ("wireRESET") == 0){
    if(gameWON){
      fakeReset = true;
      reset();
    }
  }

  val1 = analogRead(Pin1);     // read the input pin
  val2 = analogRead(Pin2); 
  val3 = analogRead(Pin3); 
  val4 = analogRead(Pin4); 
  val5 = analogRead(Pin5); 
  val6 = analogRead(Pin6);


  checkEmpty = val1 * val2 * val3 * val4 * val5 * val6;
  //checkEmpty = val1 + val2 + val3 + val4 + val5 + val6;
  emptyCount = 0;
  
  if (val1 == 0){
    emptyCount = emptyCount + 1;
  }
  if (val2 == 0){
    emptyCount = emptyCount + 1;
  }
  if (val3 == 0){
    emptyCount = emptyCount + 1;
  }
  if (val4 == 0){
    emptyCount = emptyCount + 1;
  }
  if (val5 == 0){
    emptyCount = emptyCount + 1;
  }
  
  if (emptyCount >= 2){
    if(gameWON){
      //checkEmpty = 0;
      reset();
    }
  }

  else if ( (checkEmpty != 0) && (winFlag == false) ){

    if ( (val1>60) && (val1<120) )  flag1 = 1;
    else flag1 = 0;
  
    if ( (val2>125) && (val2<195) )  flag2 = 1;
    else flag2 = 0;
  
    if ( (val3>300) && (val3<370) )  flag3 = 1;
    else flag3 = 0;
  
    if ( (val4>660) && (val4<730) )  flag4 = 1;
    else flag4 = 0;

// 
    if ( (val5>900) && (val5<960) )  flag5 = 1;
    else flag5 = 0;

 // 5 VOLTS
    if ( val6>1000 )  flag6 = 1;
    else flag6 = 0;
  
    flagCount = flag1 + flag2 + flag3 + flag4 + flag5 + flag6;
  
    if ( flagCount == 6 ){
      //winFlag = true;
      if (!gameWON)youWIN();
    }
  }
    
  

//  Serial.print("Val 1: "); Serial.print(val1); Serial.print("   ");
//  Serial.print("Val 2: "); Serial.print(val2); Serial.print("   ");
//  Serial.print("Val 3: "); Serial.print(val3); Serial.print("   ");
//  Serial.print("Val 4: "); Serial.print(val4); Serial.print("   ");
//  Serial.print("Val 5: "); Serial.print(val5); Serial.print("   ");
//  Serial.print("Val 6: "); Serial.print(val6); Serial.print("   ");
//
//  Serial.println();
  
  //Serial.println(val);
  delay(1000);

}

//=========================== FUNCTIONS ======================================================

//----------- WINNING SEQUENCE -----------------------------------------------

void youWIN(){
  if(!fakeWin) Serial.println("WIRE_WIN");
  
  digitalWrite(TEST_PIN,HIGH);
  
  winFlag = true;
  
  gameWON = true;
  fakeWin = false;
  fakeReset = false;
  
  //Serial.println("WINNER WINNER CHICKEN DINNER!!!");

  // Stay in WIN STATE until emptyCheck = 0 again
  
}

//----------- RESET PUZZLE -----------------------------------------------
void reset(){
  
  if(!fakeReset) Serial.println("WIRE_RESET");  

 for( int i=0 ; i<4 ; i++){ 
   digitalWrite(TEST_PIN,LOW);
   delay(100);
   digitalWrite(TEST_PIN,HIGH);
   delay(100);
 }

 digitalWrite(TEST_PIN,LOW);
  
  winFlag = false;
  
  gameWON = false;
  fakeReset = false;
  fakeWin = false;
  
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
