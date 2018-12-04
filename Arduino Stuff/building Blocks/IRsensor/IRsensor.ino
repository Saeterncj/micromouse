#include <SharpIR.h>


// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

#define IR_LEFT_PIN A2
#define IR_MIDDLE_LEFT_PIN A3
#define IR_MIDDLE_RIGHT_PIN A0
#define IR_RIGHT_PIN A1
#define model 1080
#define threshold 15
SharpIR sharpL(IR_LEFT_PIN, 25, 10, model);  // Each is 16bytes
SharpIR sharpM_R(IR_MIDDLE_RIGHT_PIN, 25, 10, model);
SharpIR sharpM_L(IR_MIDDLE_LEFT_PIN, 25, 10, model);
SharpIR sharpR(IR_RIGHT_PIN, 25, 10, model);


double Right_IR;
double Left_IR;
double Middle_right_IR;
double Middle_left_IR;

double PrevRight_IR;
double PrevLeft_IR;
double PrevMiddle_right_IR;
double PrevMiddle_left_IR;

volatile unsigned long counter;
void setup(){
  pinMode(IR_LEFT_PIN,INPUT);
  pinMode(IR_MIDDLE_RIGHT_PIN,INPUT);
  pinMode(IR_MIDDLE_LEFT_PIN,INPUT);
  pinMode(IR_RIGHT_PIN,INPUT);
  Serial.begin(115200);
  millis();
  //pinMode (ir, INPUT);
  
}





void loop(){
  counter = millis();
  Right_IR=sharpR.distance();      //Gets Sharp reading and return a value
  Left_IR=sharpL.distance();
  Middle_right_IR=sharpM_R.distance();
  Middle_left_IR=sharpM_L.distance();
  if(Right_IR == 0) Right_IR = PrevRight_IR;
  if(Left_IR == 0) Left_IR = PrevLeft_IR;
  if(Middle_right_IR == 0) Middle_right_IR = PrevMiddle_right_IR;
  if(Middle_left_IR == 0) Middle_left_IR = PrevMiddle_left_IR;
  Serial.print(millis()-counter);
  Serial.print("   ");
  //delay(100);
  Serial.print(Left_IR);
  Serial.print("   ");
  Serial.print(Middle_left_IR);
  Serial.print("   ");
  Serial.print(Middle_right_IR);
  Serial.print("   ");
  Serial.println(Right_IR);
  PrevRight_IR = Right_IR;
  PrevLeft_IR = Left_IR;
  PrevMiddle_right_IR = Middle_right_IR;
  PrevMiddle_left_IR = Middle_left_IR;
}
  

