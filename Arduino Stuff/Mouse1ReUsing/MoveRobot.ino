#define desired_distance  4.5

float speed_desired=0;    // Speed desired of both wheels, might need to create a speed profile
float angle_desired=0;         // angulare speed desired
float target_speed=60;
float target_angle=0;
float gfDistance_travel=0; // also in odometry
float gfActual_angle=0;

void MoveRobot(byte direction_) 
{
  static unsigned long milli_1 = 0L; 
  int done=0;
  float gfDistance_traveling;

  gfDistance_traveling=0.17;
  if(digitalRead(5)==LOW)
  {
    gfDistance_traveling=0.17 ;
  }
  gbUse_IR=1;
  //Serial.println("***************************************");
  if (direction_!=GO_STRAIGHT)
  {
    gbUse_IR=0;
    gfDistance_traveling=0.14;
      if(digitalRead(5)==LOW)
    {
      gfDistance_traveling=0.14 ;
    }
    //delay(10000);
    milli_1=millis();
    target_speed=0;
    speed_desired=0;
    //Serial.println("----------------------------------");
    if (direction_==ROTATE_LEFT)
    {
      if(target_angle==180){target_angle=-180;gfActual_angle=-180;angle_desired=-180;}
      target_angle=target_angle+93;
    }
    if (direction_==ROTATE_RIGHT)
    {
      if(target_angle==-180){target_angle=180;gfActual_angle=180;angle_desired=180;}
      target_angle=target_angle-93;
    }
    if (direction_==ROTATE_180)
    {
      target_angle=target_angle+180;
      if(target_angle>180){target_angle=target_angle-360;}
    }
    while(done==0)
    {
      if (speed_desired<target_speed){speed_desired+=0.05;}
      else if (speed_desired>target_speed){speed_desired-=0.05;}
      else{speed_desired=target_speed;}
      
      if (angle_desired<target_angle){angle_desired+=0.04;}
      else if (angle_desired>target_angle){angle_desired-=0.04;}
      else{angle_desired=target_angle;}
      
      Pid(angle_desired,speed_desired,desired_distance);
      
      motorGo(MOTOR_LEFT,abs(giPWM_left),which_way_l); 
      motorGo(MOTOR_RIGHT,abs(giPWM_right),which_way_r);
      //rotate
      
      if((gfActual_angle<float(target_angle+1)) && (gfActual_angle>float(target_angle-1)))
      {
        done=1;
      }
      if(millis()-milli_1>2000)
      {
        done=1;
      }
    }
  }
  // done rotating
  done=0;
  gfDistance_travel=0;
  gbUse_IR=1;
  while(gfDistance_travel<gfDistance_traveling)
  {
    target_speed=80;
    if(digitalRead(5)==LOW)
    {
      target_speed=80;
    }
    //go straight
//    if((gdLeft_IR<desired_distance)&&(gdRight_IR<12)){gfActual_angle=target_angle;}
//    else if((gdRight_IR<desired_distance)&&(gdLeft_IR<12)){gfActual_angle=target_angle;}

    
    if (speed_desired<target_speed){speed_desired+=0.05;}
    else if (speed_desired>target_speed){speed_desired-=0.05;}
    else{speed_desired=target_speed;}
    
    if (angle_desired<target_angle){angle_desired+=0.05;}
    else if (angle_desired>target_angle){angle_desired-=0.05;}
    else{angle_desired=target_angle;}
    
    Pid(angle_desired,speed_desired,desired_distance); 
    //Gets sensor reading inside PID() but we will get out if it is too close to wall and do adjustments
    if((gdMiddle_right_IR<12) &&(gdMiddle_left_IR<12))
    {
      adjuster();
      gfActual_angle=target_angle;
      angle_desired=target_angle;
      
      gfDistance_travel=0.17;
      gucEncoderCountL = 0;     // Used to reset Speed equal to 0!!
      gucEncodercountR = 0;

    }
    else
    {
      motorGo(MOTOR_LEFT,abs(giPWM_left),which_way_l); 
      motorGo(MOTOR_RIGHT,abs(giPWM_right),which_way_r);
    }
    
  }
  motorGo(MOTOR_LEFT,abs(0),which_way_l); 
  motorGo(MOTOR_RIGHT,abs(0),which_way_r);  // why do we command a stop?..
}
