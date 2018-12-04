#define Kp_speed      2
#define Kd_speed      0
#define Ki_speed      0.7
#define Kp_angle      1
#define Kd_angle      0.8
#define Ki_angle      0
#define integral_IR   0
/*
float Kp_speed =2, Kp_angle=1;      //porportional Gainsof PID for left and right wheel  2.2
float Kd_speed = 0.000,Kd_angle =0.8;        //derivative Gainsof PID for left and right wheel  
float Ki_speed=0.7,Ki_angle=0.0;       //Integral Gainsof PID for left and right wheel
*/




void Pid(float robot_angle,float robot_speed,float desired_distant)
{
  float counter;    // counter for debugging purposes of printing 
  if((millis()-gulLastMilli) >= LOOPTIME)   //Execute every 50 millisecond, so everything inside must happen before 50 milliseconds
  {
    gulLastMilli=millis();
    Get_IR_Readings();
    Motorspeed(robot_angle,robot_speed,desired_distant);          //Calculate speed of left and right in RPM, as well as pid
    counter=millis()/float(1000);
    Odometry();
    //PrintInfo();
   }
}


void Motorspeed(float robot_angle,float desire_robot_speed,float desired_distant)  
{  // calculate speed
  float error_IR;
  float speed_error=0;
  float angle_error=0;
  float PWM_speed=0;    // (25% = 64; 50% = 127; 75% = 191; 100% = 255)
  float PWM_angle=0;   //initialize PWM so it is in the bounday of moving also this is offset
  float PWM_IR=0;
  double Kp_IR = 14, Kd_IR = 0, Ki_IR = 0;
  static int last_speed_error=0;    
  static int last_angle_error=0;
  static int previous_IR_error=0;
  static float speed_integral_error =0, angle_integral_error=0;
  float speed_robot;
  if(gbUse_IR==1)
  {
    if((gdLeft_IR<desired_distant)&&(gdRight_IR<12)){error_IR=gdLeft_IR-desired_distant;}
    else if((gdRight_IR<desired_distant)&&(gdLeft_IR<12)){error_IR=desired_distant-gdRight_IR;}
    else if((gdLeft_IR<12)&&(gdRight_IR>12)){error_IR=gdLeft_IR-desired_distant;}
    else if((gdRight_IR<12)&&(gdLeft_IR>12)){error_IR=desired_distant-gdRight_IR;}
    else{error_IR=0;}
  }
  else
  {
    error_IR=0;
  }
 
 //Compute the actual speed of both wheels
 speed_act_L = (float(gucEncoderCountL )*(0.94971));                          // converting cts/100ms to Rev/min RPM (rrev=1,263.54cts)  w/ sampling time = 50360
 speed_act_R = (float(gucEncodercountR)*(0.94971));          
 if (which_way_l==BACKWARD &&giPWM_left<0 ){speed_act_L=-speed_act_L;}
 if (which_way_r==BACKWARD &&giPWM_right<0 ){speed_act_R=-speed_act_R;}
 speed_robot=(speed_act_L+speed_act_R)/2;
 gucEncoderCountL = 0;     // set current to previous for next iteration 
 gucEncodercountR = 0;
 
 /***************** PID***********************
  * The following code computes the output of PID which is PWM
  */
  
 speed_error =  desire_robot_speed-speed_robot;
 if ( giPWM_right < 250 && giPWM_right> -250&&giPWM_left<250 && giPWM_left> -250){speed_integral_error=speed_error+speed_integral_error; }
 PWM_speed = (Kp_speed * speed_error) + (Kd_speed * (speed_error - last_speed_error))+(Ki_speed*speed_integral_error);                            
 last_speed_error = speed_error;

 
 
 angle_error =  robot_angle-gfActual_angle;    //The desired speed for the right wheel is the left wheel 
 if (giPWM_right < 250 && giPWM_right> -250&&giPWM_left<250 && giPWM_left> -250) {angle_integral_error=angle_error+angle_integral_error; }      //Integral anti windup. 
 PWM_angle = (Kp_angle * angle_error) + (Kd_angle * (angle_error - last_angle_error))+(Ki_angle*angle_integral_error);                          
 last_angle_error= angle_error;

// if (giPWM_right < 250 && giPWM_right> -250&&giPWM_left<250 && giPWM_left> -250) {integral_IR=error_IR+integral_IR; }      //Integral anti windup. 
 PWM_IR = (Kp_IR *error_IR)+Kd_IR*(error_IR-previous_IR_error)+(Ki_IR*integral_IR);  
 previous_IR_error=error_IR;

 
 giPWM_left=PWM_speed-PWM_angle-PWM_IR;
 giPWM_right=PWM_speed+PWM_angle+PWM_IR;

 if (giPWM_left>0){giPWM_left+=15;}//offset
 else{ giPWM_left-=15;}
 if (giPWM_right>0){giPWM_right+=15;}
 else{ giPWM_right-=15;}
 // The code belows takes care of saturation or constraints on our controller
 if (giPWM_left>0){which_way_l=FORWARD;}
 else{which_way_l=BACKWARD;}
 if (giPWM_right>0){which_way_r=FORWARD;}
 else{which_way_r=BACKWARD;}
 if (giPWM_left>250)
 {
   giPWM_left=250;
 }
 if(giPWM_left<-250)
 {
   giPWM_left=-250;
 }
 if (giPWM_right>250)
 {
   giPWM_right=250;
 }
 if(giPWM_right<-250)
 {
   giPWM_right=-250;
 }
 
}
