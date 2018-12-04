//Getting to Center
byte gbDesired_state; // used by flood fill and maze and stack
byte gbWall_val;  //used in floodfill and mazeandStackts
byte gbSmallest;
byte gbPosition_state=0; //state=0 means it facing north, 1=East,2=south,3=west  *Initialized to point north


void Run1()
{
  while(!(((gbRow_coordinate==8)&&(gbCol_coordinate==8))||((gbRow_coordinate==8)&&(gbCol_coordinate==7))||((gbRow_coordinate==7)&&(gbCol_coordinate==8))||((gbRow_coordinate==7)&&(gbCol_coordinate==7))))
  {  
    if((gbRow_coordinate == 11) && (gbCol_coordinate == 4)){ delay(5000);}
    if(gaucWALL[gbRow_coordinate][gbCol_coordinate]<15) //if its not visited
    {
      //Get_PING_Readings();
      Walls_value();
      if(gbWall_val>=1 && gbWall_val <32) //If discover a wall 
      {
        push(gbRow_coordinate); //push current cell coordinates
        push(gbCol_coordinate); //push current cell coordinates
        gbCurrentRow_Coordinate=gbRow_coordinate;
        gbCurrentCol_Coordinate=gbCol_coordinate;
        AdjacentWalls();    //push all cells adjacent to the walls discovered
        ////Serial.println("I discovered a wall");
        while(stempty()==0)
        {
          //display();
          gbCol_coordinate=pop();
          gbRow_coordinate=pop();   //current_Cellvall
          if(!(((gbRow_coordinate==8)&&(gbCol_coordinate==8))||((gbRow_coordinate==8)&&(gbCol_coordinate==7))||((gbRow_coordinate==7)&&(gbCol_coordinate==8))||((gbRow_coordinate==7)&&(gbCol_coordinate==7))))
          {
            //Serial.println("-----You're in here");
            SmallestOpenNeighbors();
            if(gaucMAZE[gbRow_coordinate][gbCol_coordinate]!=gbSmallest+1)//Check to see if curr_Cell is 1 value greater than open cells
            {
              ////Serial.println("------------------You're in here");
              gaucMAZE[gbRow_coordinate][gbCol_coordinate]=gbSmallest+1; //If not, set curr_cell=min+1 and push open neighbors to stack.
              StackOpenNeighbors();
            }
          }
          //display();
          //Serial.println("---------------------");
        }
      }
    gbRow_coordinate=gbCurrentRow_Coordinate;
    gbCol_coordinate=gbCurrentCol_Coordinate;
    }

    //Move to the next minimum accessible cell
    SmallestOpenNeighbors();
    Transverse();
    //set the next cell to current cell
    UpdateCurrentCoordinate(); 
//    if ((gbRow_coordinate==11)&&(gbCol_coordinate==4))
//    {
//      motorGo(MOTOR_LEFT,0,which_way_l); 
//      motorGo(MOTOR_RIGHT,0,which_way_r);
//      delay(3000);
//    }
  }
}

void Run2()
{
  while(!((gbRow_coordinate==15)&&(gbCol_coordinate==0)))
  {  //Discovering wall and updating it   the wall array
    if((gbRow_coordinate == 11) && (gbCol_coordinate == 4)){ delay(5000);}
    if(gaucWALL[gbRow_coordinate][gbCol_coordinate]<15) //if its not visited
    {
      //Get_PING_Readings();
      Walls_value();
      if(gbWall_val>=1 && gbWall_val <32) //If discover a wall 
      {
        push(gbRow_coordinate); //push current cell coordinates
        push(gbCol_coordinate); //push current cell coordinates
        gbCurrentRow_Coordinate=gbRow_coordinate;
        gbCurrentCol_Coordinate=gbCol_coordinate;
        AdjacentWalls();    //push all cells adjacent to the walls discovered
        ////Serial.println("I discovered a wall");
        while(stempty()==0)
        {
          //display();
          gbCol_coordinate=pop();
          gbRow_coordinate=pop();   //current_Cellvall
          if(!((gbRow_coordinate==15)&&(gbCol_coordinate==0)))
          {
            //Serial.println("-----You're in here");
            SmallestOpenNeighbors();
            if(gaucMAZE[gbRow_coordinate][gbCol_coordinate]!=gbSmallest+1)//Check to see if curr_Cell is 1 value greater than open cells
            {
              ////Serial.println("------------------You're in here");
              gaucMAZE[gbRow_coordinate][gbCol_coordinate]=gbSmallest+1; //If not, set curr_cell=min+1 and push open neighbors to stack.
              StackOpenNeighbors();
            }
          }
          //display();
          //Serial.println("---------------------");
        }
      }
    gbRow_coordinate=gbCurrentRow_Coordinate;
    gbCol_coordinate=gbCurrentCol_Coordinate;
    }

    //Move to the next minimum accessible cell
    SmallestOpenNeighbors();
    Transverse();
    //set the next cell to current cell
    UpdateCurrentCoordinate(); 
//    if ((gbRow_coordinate==11)&&(gbCol_coordinate==4))
//    {
//      motorGo(MOTOR_LEFT,0,which_way_l); 
//      motorGo(MOTOR_RIGHT,0,which_way_r);
//      delay(3000);
//    }
  }
}

//Getting to Center
void Run3()
{
  while(!(((gbRow_coordinate==8)&&(gbCol_coordinate==8))||((gbRow_coordinate==8)&&(gbCol_coordinate==7))||((gbRow_coordinate==7)&&(gbCol_coordinate==8))||((gbRow_coordinate==7)&&(gbCol_coordinate==7))))
  {  //Discovering wall and updating it   the wall array

    if(gaucWALL[gbRow_coordinate][gbCol_coordinate]<15) //if its not visited
    {
      //Get_PING_Readings();
      Walls_value();
      if(gbWall_val>=1 && gbWall_val <32) //If discover a wall 
      {
        push(gbRow_coordinate); //push current cell coordinates
        push(gbCol_coordinate); //push current cell coordinates
        gbCurrentRow_Coordinate=gbRow_coordinate;
        gbCurrentCol_Coordinate=gbCol_coordinate;
        AdjacentWalls();    //push all cells adjacent to the walls discovered
        while(stempty()==0)
        {
          //display();
          gbCol_coordinate=pop();
          gbRow_coordinate=pop();   //current_Cellvall
          if(!(((gbRow_coordinate==8)&&(gbCol_coordinate==8))||((gbRow_coordinate==8)&&(gbCol_coordinate==7))||((gbRow_coordinate==7)&&(gbCol_coordinate==8))||((gbRow_coordinate==7)&&(gbCol_coordinate==7))))
          {
            SmallestOpenNeighbors();
            if(gaucMAZE[gbRow_coordinate][gbCol_coordinate]!=gbSmallest+1)//Check to see if curr_Cell is 1 value greater than open cells
            {
              gaucMAZE[gbRow_coordinate][gbCol_coordinate]=gbSmallest+1; //If not, set curr_cell=min+1 and push open neighbors to stack.
              StackOpenNeighbors();
            }
          }
        }
      }
    gbRow_coordinate=gbCurrentRow_Coordinate;
    gbCol_coordinate=gbCurrentCol_Coordinate;
    
    }
    //Move to the next minimum accessible cell
    SmallestOpenNeighbors();
    Transverse();
    //set the next cell to current cell
    UpdateCurrentCoordinate(); 
    if(digitalRead(5)==LOW)
    {
      gbRow_coordinate=15;
      gbCol_coordinate=0;
      gbPosition_state=0;
      gbDesired_state=0;
      delay(10000);
    }
  }
}
