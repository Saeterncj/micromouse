float speed_act_L = 0;                              // speed (actual value)
float speed_act_R = 0;                              // speed (actual value) used in odometry and pid

void Odometry()
{
//  float L=.08;
//  float r=.016;
//  float Ts=.05;
//  float R=.08;
  float pi = 3.14159;
  float L=.08;
  float r=.035;
  float Ts=.05;
  float v_r,v_l;  
  float w_robot;
  float v_robot;
  float instantaneous_curve;
  float x=0,y=0;
  v_r=speed_act_R*2*pi*r/60;
  v_l=speed_act_L*2*pi*r/60;
  v_robot=(v_l+v_r)/2;
  w_robot=(v_r-v_l)/L;
  instantaneous_curve=v_robot/w_robot;
  gfActual_angle = gfActual_angle+w_robot*Ts*180/pi;    //in degrees
  x = x+(v_l+v_r)*cos(gfActual_angle*pi/180)*Ts/2;
  y = y+(v_l+v_r)*sin(gfActual_angle*pi/180)*Ts/2;
  gfDistance_travel+=v_robot*Ts;
}
