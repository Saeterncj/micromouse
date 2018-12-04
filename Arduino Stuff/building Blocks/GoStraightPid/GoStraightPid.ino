
/*  Created By: Cheng Saetern
 *  Date Created: 3/3/2017
 *  Description:    This file will be an update of motor. This will utilize encoder and                
 *                  motor with pid to control speed of left and right wheel
 *  
 */

 
volatile unsigned long countL = 0L;                      // encoder counter for left
volatile unsigned long countR = 0L;                      // encoder counter for right

extern double actualSpeedL; //  rev/min
extern double actualSpeedR; //  rev/min

//------------------------- Motor Suff -----------------------------
#define MOTOR_LEFT                0
#define MOTOR_RIGHT               1
#define FORWARD                   2     //Direction of Motors
#define BACKWARD                  3
#define STOP                      4

volatile unsigned long prevMill = 0;


void setup() {
  // put your setup code here, to run once:
  InitMotors();
  InitEncoder();
  Serial.begin(115200);
  
}

void loop() {
//  for(int i = 0; i < 65;)
//  {
//    if(millis()- prevMill > 50)
//    {
//      i++;
//      prevMill = millis();
//      
//    }
    pidMotorSpeed(0);
  //}
  

}
