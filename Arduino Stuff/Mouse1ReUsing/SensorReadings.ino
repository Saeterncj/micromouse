//Get all sensor Readings
//Get just front sensor reading for adjustment

// SHARP SENSOR
#define ENCODER_PIN_RIGHT_A         2                       // Right Motor encoder A phase
#define ENCODER_PIN_LEFT_A          3                      // Left Motor encoder A phase

void InitIR()
{
  pinMode(IR_LEFT_PIN,INPUT);
  pinMode(IR_MIDDLE_RIGHT_PIN,INPUT);
  pinMode(IR_MIDDLE_LEFT_PIN,INPUT);
  pinMode(IR_RIGHT_PIN,INPUT);
}

void Get_IR_Readings()      //Can be adjust to get multiple readings beofre exiting
{
  double prevRight = gdRight_IR;
  double prevLeft = gdLeft_IR;
  double prevMiddleRight = gdMiddle_right_IR;
  double prevMiddleLeft = gdMiddle_left_IR;
  gdRight_IR=sharpR.distance();      //Gets Sharp reading and return a value
  gdLeft_IR=sharpL.distance();
  gdMiddle_right_IR=sharpM_R.distance();
  gdMiddle_left_IR=sharpM_L.distance();
  
 if(gdMiddle_right_IR == 0){gdMiddle_right_IR=prevMiddleRight;}
 if(gdMiddle_left_IR == 0){gdMiddle_left_IR=prevMiddleLeft;}
 if(gdRight_IR == 0){gdRight_IR=prevRight;}
 if(gdLeft_IR ==0){gdLeft_IR=prevLeft;}
}

void Get_Front_IR_Readings()      //Can be adjust to get multiple readings beofre exiting
{
  double prevMiddleRight = gdMiddle_right_IR;
  double prevMiddleLeft = gdMiddle_left_IR;
  gdMiddle_right_IR=sharpM_R.distance();
  gdMiddle_left_IR=sharpM_L.distance();
  if(gdMiddle_right_IR == 0){gdMiddle_right_IR=prevMiddleRight;}
  if(gdMiddle_left_IR == 0){gdMiddle_left_IR=prevMiddleLeft;}
// if(gdMiddle_right_IR<0){gdMiddle_right_IR=50;}
// if(gdMiddle_left_IR<0){gdMiddle_left_IR=50;}
}
void InitEncoder(){
   pinMode(ENCODER_PIN_RIGHT_A, INPUT); 
   pinMode(ENCODER_PIN_LEFT_A, INPUT); 
   digitalWrite(ENCODER_PIN_RIGHT_A, HIGH);                      // turn on pullup resistor
   digitalWrite(ENCODER_PIN_LEFT_A, HIGH);
   attachInterrupt(0, rencoderR, CHANGE);     //Arduino Mega Interupt pines 0=pin2, 1=pin3,2=pin21,3=pin20,4=pin19,5=pin18
   attachInterrupt(1, rencoderL, CHANGE);
}

 // B(dgital pin 8-13), 
 //D(digital PIN(0-7) 7th pin on the left 7,6,5,4,3,2,1,0
void rencoderR()  {                                 // pulse and direction, direct port reading to save cycles
  gucEncodercountR++;
 //if (PIND & 0b00001000)    gucEncodercountR++;                // if(digitalRead(ENCODER_PIN_LEFT)==HIGH)   count ++;
 //else                      gucEncodercountR++;                // if (digitalRead(ENCODER_PIN_LEFT)==LOW)   count --;
}
void rencoderL()  {                                    // pulse and direction, direct port reading to save cycles
 gucEncoderCountL++;
 //if (PIND & 0b00000100)    gucEncoderCountL++;                // if(digitalRead(ENCODER_PIN_LEFT)==HIGH)   count ++;
 //else                      gucEncoderCountL++;                // if (digitalRead(ENCODER_PIN_LEFT)==LOW)   count --;
}
