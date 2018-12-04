#define ADJ_TIME          1000
#define Kp_L              10
#define Kp_R              10
#define Kd_L              2.5
#define Kd_R              3.4
#define Ki_L              0
#define Ki_R              0
#define distant_desired   6

void adjuster() 
{
  static unsigned long milli = 0L;               // loop timing
 milli=millis();
 while((millis()-milli) <= ADJ_TIME)   
 { 
  if((millis()-gulLastMilli) >= LOOPTIME)   
   { 
      gulLastMilli=millis();
      Motorspeed1();          //Calculate speed of left and right in RPM
   }  
 }
}


void Motorspeed1()  
{  // calculate speed
float error_L=0;      //Changing it to FLOAT really MATTERS
float error_R=0;

static int last_error_L=0;    
static int last_error_R=0;
static double error_integral_L =0, error_integral_R=0;
static double prevMiddleRightIR;
static double prevMiddleLeftIR;

 gdMiddle_right_IR= sharpM_R.distance();
 gdMiddle_left_IR = sharpM_L.distance();
 if(gdMiddle_right_IR<0){gdMiddle_right_IR=prevMiddleRightIR;}
 if(gdMiddle_left_IR<0){gdMiddle_left_IR=prevMiddleLeftIR;}
 if(gdMiddle_right_IR > 20){gdMiddle_right_IR=prevMiddleRightIR;}
 if(gdMiddle_left_IR > 20){gdMiddle_left_IR=prevMiddleLeftIR;}
  prevMiddleLeftIR = gdMiddle_left_IR;
  prevMiddleRightIR = gdMiddle_right_IR;
 
 error_L = gdMiddle_left_IR-distant_desired;
 error_integral_L=error_L+error_integral_L; 
 if(error_integral_L>80){error_integral_L=80;}
 giPWM_left = (Kp_L * error_L) + (Kd_L * (error_L - last_error_L))+(Ki_L*error_integral_L);                            
 last_error_L = error_L;
 
 error_R = gdMiddle_right_IR-distant_desired;
 error_integral_R=error_R+error_integral_R; 
 if(error_integral_R>80){error_integral_R=80;}
 giPWM_right = (Kp_R * error_R) + (Kd_R * (error_R - last_error_R))+(Ki_R*error_integral_R);                            
 last_error_R= error_R;
 if (giPWM_left>0){giPWM_left+=15;}//offset
 else{ giPWM_left-=15;}
 if (giPWM_right>0){giPWM_right+=15;}
 else{ giPWM_right-=15;}
 
 if(error_L<0){which_way_l=BACKWARD;}
 else{which_way_l=FORWARD;}
 if(error_R<0){which_way_r=BACKWARD;}
 else{which_way_r=FORWARD;}
 giPWM_right=abs(giPWM_right);
 giPWM_left=abs(giPWM_left);
 if (giPWM_left>250)
 {
   giPWM_left=250;
 }
 if(giPWM_left<5)
 {
   giPWM_left=5;
 }
 if (giPWM_right>250)
 {
   giPWM_right=250;
 }
 if(giPWM_right<5)
 {
   giPWM_right=5;
 }
 
 motorGo(MOTOR_LEFT,giPWM_left,which_way_l); 
 motorGo(MOTOR_RIGHT,giPWM_right,which_way_r);
}
