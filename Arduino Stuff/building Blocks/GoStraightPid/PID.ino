#define SAMPLING_TIME   50     // Sampling every 100ms

unsigned long lastMilli = 0L;                    // use to remember last milli
double actualSpeedL; //  rev/min
double actualSpeedR; //  rev/min
void pidMotorSpeed(double desiredSpeed)
{
  static double errorP,errorI_L = 0,errorI_R = 0;
  static double speed_KpR = 2, speed_KiR=.7,speedKdR=0;
  static double speed_KpL = 2, speed_KiL=.7,speedKdL=0;
  static int ucPwmLeft, ucPwmRight;
  static int direction_ = FORWARD;
  
  if(millis()-lastMilli > SAMPLING_TIME)
  {
    lastMilli = millis();
    actualSpeedL = (double)countL*0.94971;     // converting cts/100ms to Rev/min RPM (rrev=1,263.54cts)  w/ sampling time = 50
    actualSpeedR = (double)countR*0.94971;
    countR=0;
    countL=0;

    errorP = desiredSpeed - actualSpeedL;
    errorI_L += errorP;
    ucPwmLeft = speed_KpL * errorP + speed_KiL*errorI_L;

    errorP = desiredSpeed - actualSpeedR;
    errorI_R += errorP;
    ucPwmRight = speed_KpR * errorP + speed_KiR*errorI_R;
    
    
    motorGo(MOTOR_LEFT,ucPwmLeft,direction_);
    motorGo(MOTOR_RIGHT,ucPwmRight,direction_);
    Serial.print(ucPwmLeft);
    Serial.print("       ");
    Serial.print(ucPwmRight);
    Serial.print("       ");
    Serial.print(actualSpeedL);
    Serial.print("       ");
    Serial.println(actualSpeedR);
    
  }
}


  // put your main code here, to run repeatedly:


  //MotorControl( ucPwmLeft, ucPwmRight);
  
  
