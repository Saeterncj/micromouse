// Mouse 1


volatile unsigned long milli;
#define ADJ_TIME 10000   // give it 2 seconds to adjust
#define LOOPTIME 50       // loop every 50ms

double distant_desired = 7;

void adjuster() 
{
 milli=millis();
 while((millis()-milli) <= ADJ_TIME)   
 { 
  if((millis()-lastMilli) >= LOOPTIME)   
   { 
      lastMilli=millis();
      Motorspeed1();          //Calculate speed of left and right in RPM
    
   }
  
 }
}


void Motorspeed1()  
{  // calculate speed
double error_L=0;      //Changing it to FLOAT really MATTERS
double error_R=0;
static double error_integral_L, error_integral_R;
int PWM_left,PWM_right;
static double last_error_L=0;    
static double last_error_R=0;
double Kp_L=10,Kd_L=2.5,Ki_L=0;
double Kp_R=10,Kd_R=3.4,Ki_R=0;
int which_way_l,which_way_r;
double Middle_right_IR,Middle_left_IR;

 Middle_right_IR= sharpM_R.distance()/5.75;
 Middle_left_IR = sharpM_L.distance()/5.75;
 if(Middle_right_IR<0){Middle_right_IR=50;}
 if(Middle_left_IR<0){Middle_left_IR=50;}
 if(Middle_right_IR>20){Middle_right_IR=20;}
 if(Middle_left_IR>20){Middle_left_IR=20;}
 
 
 error_L = Middle_left_IR-distant_desired;
 error_integral_L=error_L+error_integral_L; 
 if(error_integral_L>80){error_integral_L=80;}
 PWM_left = (Kp_L * error_L) + (Kd_L * (error_L - last_error_L))+(Ki_L*error_integral_L);                            
 last_error_L = error_L;
 
 error_R = Middle_right_IR-distant_desired;
 error_integral_R=error_R+error_integral_R; 
 if(error_integral_R>80){error_integral_R=80;}
 PWM_right = (Kp_R * error_R) + (Kd_R * (error_R - last_error_R))+(Ki_R*error_integral_R);                            
 last_error_R= error_R;
 if (PWM_left>0){PWM_left+=15;}//offset
 else{ PWM_left-=15;}
 if (PWM_right>0){PWM_right+=15;}
 else{ PWM_right-=15;}
 
 if(error_L<0){which_way_l=BACKWARD;}
 else{which_way_l=FORWARD;}
 if(error_R<0){which_way_r=BACKWARD;}
 else{which_way_r=FORWARD;}
 PWM_right=abs(PWM_right);
 PWM_left=abs(PWM_left);
 if (PWM_left>250)
 {
   PWM_left=250;
 }
 if(PWM_left<5)
 {
   PWM_left=5;
 }
 if (PWM_right>250)
 {
   PWM_right=250;
 }
 if(PWM_right<5)
 {
   PWM_right=5;
 }
 
 motorGo(MOTOR_LEFT,PWM_left,which_way_l); 
 motorGo(MOTOR_RIGHT,PWM_right,which_way_r);
}
