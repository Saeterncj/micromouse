


// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)



void InitIr(){
  pinMode(IR_LEFT_PIN,INPUT);
  pinMode(IR_MIDDLE_RIGHT_PIN,INPUT);
  pinMode(IR_MIDDLE_LEFT_PIN,INPUT);
  pinMode(IR_RIGHT_PIN,INPUT);
  Serial.begin(115200);
  //pinMode (ir, INPUT);
  
}

  

