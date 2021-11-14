

/*  Created By: Cheng Saetern
 *  Date Created: 3/4/2017
 *  Description:    This code is a reuse of Cheng's previous code.  
 *                  The goal is to be able to be able to modify this code to complement 
 *                  the new mouse.   
 */
 

#define ARRAY_SIZE         16
#define MAXSIZE             256
#define HIGH_VAL            254

// ChengChange change size
//#define size 1023
#define SIZE 600        // Stack size


// Majority of the memory is beacause of this STACK!!!!!!!!
// Need to really define the size and the top!
struct stack {   
   uint8_t s[SIZE];
   int top;
} st;
 
uint8_t gaucMAZE[ARRAY_SIZE][ARRAY_SIZE]; //Create a maze 16x16 to store values to each cell

byte gbRow_coordinate=15;
byte gbCol_coordinate=0;
byte gbCurrentRow_Coordinate;
byte gbCurrentCol_Coordinate;


//byte current_cell;

// ChengChang commented out the below
//byte curr_cell;
//byte gbSmallest;

// ChengChang commented out the below
//uint8_t n =0; //u_int8_t save a byte lol *only use n for void loop atm

// ChengChang commented out the below
//float follow_distance=5;


uint8_t gaucWALL[ARRAY_SIZE][ARRAY_SIZE]={0}; //Initialize all to 0. byte is from 0-255
// int8_t wtf=127; //ranges from -128 => 127




// ------------------------------------------------------- IR STUFF -----------------------------------------------
#include <SharpIR.h>
#define IR_LEFT_PIN A2
#define IR_MIDDLE_LEFT_PIN A3
#define IR_MIDDLE_RIGHT_PIN A0
#define IR_RIGHT_PIN A1
#define model 1080
#define threshold 10
SharpIR sharpL(IR_LEFT_PIN, 15, 93, model);  // Each is 16bytes
SharpIR sharpM_R(IR_MIDDLE_RIGHT_PIN, 15, 93, model);
SharpIR sharpM_L(IR_MIDDLE_LEFT_PIN, 15, 93, model);
SharpIR sharpR(IR_RIGHT_PIN, 15, 93, model);
// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)
// Setup
// IR purposes
double gdRight_IR=1;
double gdLeft_IR=1;
double gdMiddle_right_IR=50;
double gdMiddle_left_IR=50;

//-------------------------------------------------- MOTOR and ENCODER PINS  ------------------------------------------

#define MOTOR_LEFT                0
#define MOTOR_RIGHT               1
#define FORWARD                   1     //Direction of Motors
#define BACKWARD                  2
#define STOP                      3
//------------------------------------------------ PID   -------------------------------------------------------
#define LOOPTIME                 50                    //loop every 50 milliseconds (sampling time)
unsigned long gulLastMilli = 0L;                    // use to remember last milli
volatile unsigned long gucEncoderCountL = 0L;                      // encoder counter for left
volatile unsigned long gucEncodercountR = 0L;                      // encoder counter for right
int giPWM_left=1;   
int giPWM_right=1;

uint8_t which_way_l=FORWARD;
uint8_t which_way_r=FORWARD;    //initialize to go FORWARD=1

byte gbUse_IR=0;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-  SET UP  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//int inf=0;
void setup() 
{
  
  Serial.begin(115200);
  InitMotor();
  InitIR();
  InitEncoder();
  Initialize_Maze();
  pinMode(5,INPUT);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  Serial.println("Init Done");
  //current_cell=gaucMAZE[gbRow_coordinate][gbCol_coordinate];  // why do we need this? when it isnt used anywhere else?
  st.top=-1;
}

//**************************************************  MAIN LOOP    *******************************************
void loop() 
{
  Run1();
  
  delay(1000);
  Serial.println("It is sending");
  displayRealWall();
  gbCurrentRow_Coordinate=gbRow_coordinate;
  gbCurrentCol_Coordinate=gbCol_coordinate;
  InitBackMaze();
  displayRealWall();
  gbRow_coordinate=gbCurrentRow_Coordinate;
  gbCol_coordinate=gbCurrentCol_Coordinate;
//  PrintMaze(); 
//  PrintWall();
  Run2();
  //Need to do Run3()!!!
  gbCurrentRow_Coordinate=15;
  gbCurrentCol_Coordinate=0;
  InitMaze2();
  gbRow_coordinate=gbCurrentRow_Coordinate;
  gbCol_coordinate=gbCurrentCol_Coordinate;
  digitalWrite(4,LOW);
}
