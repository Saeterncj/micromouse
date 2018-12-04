void PrintInfo()  
{                                                      // display data

  //Odometry(); 
//   Serial.print(counter);   
//   Serial.print(",");
  //---------------------------------------   SPEED  ----------------------------------
//   Serial.print(" Speed Desired:");          
//   Serial.print(speed_desired,2);
//   Serial.print(" Speed target:");          
//   Serial.print(target_speed,2);
//   Serial.print("LEFT RPM:");               
//   Serial.print(speed_act_L,2);   
//   Serial.print(" :RIGHT RPM:");  
//   Serial.print(speed_act_R,2); 
//   Serial.print("target speed:");
//   Serial.print(target_speed,2);
//   Serial.print(" ,  "); 
//   Serial.print(speed_robot,2);
//   Serial.print(" Angle Desired: "); 
//   Serial.print(angle_desired,2);
//   Serial.print(" , ");   
//   Serial.print(gfActual_angle,4);
   //--------------------------------------   PWM  ------------------------------- 
//   Serial.print(" LEFT PWM::");         
//   Serial.print(giPWM_left);
//   Serial.print(" :RIGHT PWM:");    
//   Serial.print(giPWM_right);
//   Serial.print(" :PWM_SPEED:");
//   Serial.print( PWM_speed);
//   Serial.print(" :integral error:");
//   Serial.print(speed_integral_error);

//   Serial.print(" :PWM_Sangle:");
//   Serial.print( PWM_angle);
//   Serial.print(" :PWM_IR:");
//   Serial.print( PWM_IR);
   // -------------------------------------  Sensors  ---------------------------------
   
//   Serial.print(" which way left");
//   Serial.print( which_way_l);
//   Serial.print(" which way right");
//   Serial.print( which_way_r);
//   Serial.print(",");
//   Serial.print(" :LEFT encoder:");          
//   Serial.print(gucEncodercountR); 
//   Serial.print(" :RIGHT encoder:");          
//   Serial.print(gucEncoderCountL); 
//   Serial.print(",");       
//   Serial.print(gdLeft_IR);
//   Serial.print(",");   
//  Serial.print(" gdLeft_IR ");
//  Serial.print(gdLeft_IR);
//  Serial.print(" gdMiddle_right_IR ");
//  Serial.print(gdMiddle_right_IR);
//  Serial.print(" Middle_leftt_IR ");
//  Serial.print(gdMiddle_left_IR);
//  Serial.print(" gdRight_IRR ");
//  Serial.print(gdRight_IR);           
   //------------------------------------------ Odometry  ------------------------------------
//   Serial.print("  Distance Traveled: ");
//   Serial.print(gfDistance_travel);
//   Serial.print(x,4); 
//   Serial.print(" , ");
//   Serial.print(y,4);   
//   Serial.print(" , "); 
//   Serial.print(w_robot,4);   
//   Serial.print(",");                    
//   Serial.print(instantaneous_curve,4);
//   Serial.println("");
}

void PrintMaze()
{ 
  static uint8_t counter=0;
  for(int j=0;j<ARRAY_SIZE*ARRAY_SIZE;j++){
    counter++;
    if(counter==ARRAY_SIZE){
      Serial.println(gaucMAZE[0][j]);
      counter=0;
    }
    else{
      Serial.print(gaucMAZE[0][j]);
      Serial.print("  ");
    }
  
  }
  Serial.println("");
}
void PrintWall()
{
  
  static uint8_t counter=0;
  for(int j=0;j<ARRAY_SIZE*ARRAY_SIZE;j++){
    counter++;
    if(counter==ARRAY_SIZE){
      Serial.println(gaucWALL[0][j]);
      counter=0;
    }
    else{
      Serial.print(gaucWALL[0][j]);
      Serial.print("  ");
    }
  
  }
  Serial.println("");
}

void displayRealWall(void)
{
  uint8_t row, column;
  for (row = 0; row < 33; row++)
  {
    for (column = 0; column < 33; column++)
    {
      //Serial.print("%3d ", Maze[row][column]);
      // if odd skip 
      if ((row % 2 == 0) && (column % 2 == 0))
      {
        Serial.print("+");
      }
      else if ((row % 2 == 1) && (column % 2 == 0))
      {
        if ((gaucWALL[row / 2][(column + 1) / 2] & 8) || (gaucWALL[row / 2][(column + 1) / 2 - 1] & 2))
        {
          Serial.print("|");
        }
         else
         {
           Serial.print(" ");
         }
        
        
      }
      else if ((row % 2 == 0) && (column % 2 == 1))
      {
        //Serial.print("--");
        if ((gaucWALL[row / 2][(column) / 2] & 1) || (gaucWALL[row / 2 - 1][(column) / 2] & 4))
        {
          Serial.print("--");
        }
        else
        {
          Serial.print("  ");
        }
      }
      else
      {
        //Serial.print(" ");
        if (gaucMAZE[row / 2][column / 2] / 10)
          Serial.print(gaucMAZE[row / 2][column / 2]);
        else
        {
         Serial.print(" ");
         Serial.print(gaucMAZE[row / 2][column / 2]);
        }
      }
      
    }
    Serial.println("");
  }
}


