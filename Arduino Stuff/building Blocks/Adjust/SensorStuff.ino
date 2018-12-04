
#define ENCODER_PIN_RIGHT_A         2                       // Right Motor encoder A phase
#define ENCODER_PIN_LEFT_A          3                      // Left Motor encoder A phase

void InitEncoder(){
   pinMode(ENCODER_PIN_RIGHT_A, INPUT); 
   pinMode(ENCODER_PIN_LEFT_A, INPUT); 
   digitalWrite(ENCODER_PIN_RIGHT_A, HIGH);                      // turn on pullup resistor
   digitalWrite(ENCODER_PIN_LEFT_A, HIGH);
   attachInterrupt(0, rencoderR, CHANGE);     //Arduino Mega Interupt pines 0=pin2, 1=pin3,2=pin21,3=pin20,4=pin19,5=pin18
   attachInterrupt(1, rencoderL, CHANGE);
}

void rencoderR()  {                                 // pulse and direction, direct port reading to save cycles
  countR++;
 //if (PIND & 0b00001000)    countR++;                // if(digitalRead(ENCODER_PIN_LEFT)==HIGH)   count ++;
 //else                      countR++;                // if (digitalRead(ENCODER_PIN_LEFT)==LOW)   count --;
}

void rencoderL()  {                                    // pulse and direction, direct port reading to save cycles
 countL++;
 //if (PIND & 0b00000100)    countL++;                // if(digitalRead(ENCODER_PIN_LEFT)==HIGH)   count ++;
 //else                      countL++;                // if (digitalRead(ENCODER_PIN_LEFT)==LOW)   count --;
}



