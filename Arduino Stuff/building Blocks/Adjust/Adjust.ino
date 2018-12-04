// Mouse 1
/*  Created By: Cheng Saetern
 *  Date Created: 3/3/2017
 *  Description:    This code allows the robot to adjust its position from a wall infront of it. 
 *                  Adjust until both sides are equal.
 *  
 */

#include <SharpIR.h>

volatile unsigned long countL = 0L;                      // encoder counter for left
volatile unsigned long countR = 0L;                      // encoder counter for right

extern double actualSpeedL; //  rev/min
extern double actualSpeedR; //  rev/min
// ------------------------ IR Stuff ---------------------
#define IR_LEFT_PIN A2
#define IR_MIDDLE_LEFT_PIN A3
#define IR_MIDDLE_RIGHT_PIN A0
#define IR_RIGHT_PIN A1
#define model 1080
#define threshold 15
SharpIR sharpL(IR_LEFT_PIN, 25, 93, model);  // Each is 16bytes
SharpIR sharpM_R(IR_MIDDLE_RIGHT_PIN, 25, 93, model);
SharpIR sharpM_L(IR_MIDDLE_LEFT_PIN, 25, 93, model);
SharpIR sharpR(IR_RIGHT_PIN, 25, 93, model);


double Right_IR;
double Left_IR;
double Middle_right_IR;
double Middle_left_IR;

//------------------------- Motor Suff -----------------------------
#define MOTOR_LEFT                0
#define MOTOR_RIGHT               1
#define FORWARD                   2     //Direction of Motors
#define BACKWARD                  3
#define STOP                      4

volatile unsigned long prevMill = 0;
unsigned long lastMilli = 0L;                    // use to remember last milli

void setup() {
  // put your setup code here, to run once:
  InitMotors();
  InitEncoder();
  Serial.begin(115200);
  
}

void loop() {
  adjuster();
}
