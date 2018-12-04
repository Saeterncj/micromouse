
/*  Created By: Cheng Saetern
 *  Date Created: 3/3/2017
 *  Description:    This file is for the motor only. 
 *              It will demonstrate that it can go forward and backwards.
 *              Two different functions may be called to move the motors                   
 *  
 */

#define MOTOR_LEFT                0
#define MOTOR_RIGHT               1
#define FORWARD                   2     //Direction of Motors
#define BACKWARD                  3
#define STOP                      4

void setup() {
  // put your setup code here, to run once:
  InitMotors();
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint8_t ucPwmLeft, ucPwmRight;
  static uint8_t direction_ = FORWARD;
  ucPwmLeft++;
  ucPwmRight++;

  //MotorControl( ucPwmLeft, ucPwmRight);
  motorGo(MOTOR_LEFT,ucPwmLeft,direction_);
  motorGo(MOTOR_RIGHT,ucPwmRight,direction_);
  
  if(ucPwmLeft > 30)
  {
    ucPwmLeft = 0;
    if(direction_ == FORWARD) direction_ = BACKWARD;
    else direction_ = FORWARD;
  }
  if(ucPwmRight > 30)
  {
    ucPwmRight = 0;
  }
  Serial.print(ucPwmLeft);
  Serial.print("     ");
  Serial.println(ucPwmRight);
  delay(250);
}
