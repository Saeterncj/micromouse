// Motor Pins
#define PWM_YELLOW_PIN   9
#define INA_YELLOW_PIN   7    //Yellow is right
#define INB_YELLOW_PIN   8   //Right blue on A02, Right green on A01

#define INA_BLUE_PIN  4   ////Left blue on B01, Right green on B02
#define INB_BLUE_PIN  5
#define PWM_BLUE_PIN  6   //Blue is left

// Prueba set point
double distancia = 0;

void InitMotors(){
  
 
  pinMode(PWM_BLUE_PIN, OUTPUT);  
  pinMode(PWM_YELLOW_PIN, OUTPUT); 
  pinMode(INA_BLUE_PIN, OUTPUT);
  pinMode(INB_BLUE_PIN, OUTPUT);  
  pinMode(INA_YELLOW_PIN, OUTPUT);  
  pinMode(INB_YELLOW_PIN, OUTPUT); 
 
  digitalWrite(INA_BLUE_PIN,HIGH); 
  digitalWrite(INB_BLUE_PIN,HIGH); 
  digitalWrite(INA_YELLOW_PIN,HIGH); 
  digitalWrite(INB_YELLOW_PIN,HIGH); 
  
}

void Stop(){
  digitalWrite(INA_BLUE_PIN,LOW); 
  digitalWrite(INB_BLUE_PIN,LOW); 
  digitalWrite(INA_YELLOW_PIN,LOW); 
  digitalWrite(INB_YELLOW_PIN,LOW); 
  analogWrite(PWM_BLUE_PIN, 0);
  analogWrite(PWM_YELLOW_PIN, 0);
}



void motorGo(byte motor,int PWM_val,byte direction_){  
 if(PWM_val > 255) PWM_val = 255;
 if(PWM_val < 0) PWM_val = 0;
 if(motor == MOTOR_LEFT&& direction_==FORWARD){
   //digitalWrite(InA_Left_PIN, LOW);
   digitalWrite(INA_BLUE_PIN,HIGH);
   digitalWrite(INB_BLUE_PIN,LOW); // go forward leftmotor
   analogWrite(PWM_BLUE_PIN, PWM_val);   
   
 }
 else if(motor == MOTOR_RIGHT&& direction_==FORWARD){
   //digitalWrite(InA_Right_PIN, LOW);
   digitalWrite(INA_YELLOW_PIN,HIGH);  // go forward right motor
   digitalWrite(INB_YELLOW_PIN,LOW);
   analogWrite(PWM_YELLOW_PIN, PWM_val);  
 }
 else if(motor == MOTOR_LEFT&& direction_==BACKWARD){
   //digitalWrite(InA_Left_PIN, HIGH);
   digitalWrite(INA_BLUE_PIN,LOW); // go backward left motor
   digitalWrite(INB_BLUE_PIN,HIGH);
   analogWrite(PWM_BLUE_PIN, PWM_val);   
 }
 else if(motor == MOTOR_RIGHT && direction_==BACKWARD){
    //digitalWrite(InA_Right_PIN, HIGH);
    digitalWrite(INA_YELLOW_PIN,LOW);
    digitalWrite(INB_YELLOW_PIN,HIGH); // go baackward right motor
    analogWrite(PWM_YELLOW_PIN, PWM_val); 
 }
 if(motor == MOTOR_LEFT && direction_==STOP ){
   analogWrite(PWM_BLUE_PIN, 0);
   digitalWrite(INA_BLUE_PIN,LOW); 
   digitalWrite(INB_BLUE_PIN,LOW);

 }
 if(motor == MOTOR_RIGHT  && direction_==STOP){
   analogWrite(PWM_YELLOW_PIN, 0);
   digitalWrite(INA_YELLOW_PIN,LOW);
    digitalWrite(INB_YELLOW_PIN,LOW); // go baackward right motor
 }
}

//Blue is left, Yellow is right
void MotorControl(int pwmLeft,int pwmRight){

 
  // Sets direction, may need to swith the positions around
  if (pwmLeft < 0){
    digitalWrite(INA_BLUE_PIN,LOW); // go backward left motor
    digitalWrite(INB_BLUE_PIN,HIGH);
  }else{
    digitalWrite(INA_BLUE_PIN,HIGH);
    digitalWrite(INB_BLUE_PIN,LOW); // go forward leftmotor
  }

  if( pwmRight < 0) {
    digitalWrite(INA_YELLOW_PIN,LOW);
    digitalWrite(INB_YELLOW_PIN,HIGH); // go baackward right motor
  } else {
    digitalWrite(INA_YELLOW_PIN,HIGH);  // go forward right motor
    digitalWrite(INB_YELLOW_PIN,LOW);
  }
  
  if (pwmLeft<0) pwmLeft = abs(pwmLeft);
  if (pwmLeft > 240) pwmLeft=240;
  if (pwmRight <0) pwmRight = abs(pwmRight);
  if (pwmRight > 240) pwmRight=240;
  
  //Serial.println(out);
  analogWrite(PWM_BLUE_PIN, pwmLeft);
  analogWrite(PWM_YELLOW_PIN, pwmRight);
}




