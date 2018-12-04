void GoBackMaze()
{ 
  static uint8_t counter=0;
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    for(int j=0;j<ARRAY_SIZE;j++)
    {
      gaucMAZE[i][j]=255;
    }
  }
  gaucMAZE[15][0]=0;
}
void InitOptimal()
{ 
  static uint8_t counter=0;
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    for(int j=0;j<ARRAY_SIZE;j++)
    {
      gaucMAZE[i][j]=255;
    }
  }
  gaucMAZE[8][7]=0;
  gaucMAZE[7][7]=0;
  gaucMAZE[7][8]=0;
  gaucMAZE[8][8]=0;
}

void InitBackMaze() 
{
  GoBackMaze();
  // Might need to push 15 0?... 
  push(14);
  push(0);

  while(stempty()==0)
  {
    gbCol_coordinate=pop();
    gbRow_coordinate=pop();   //current_Cellvall
    if(!((gbRow_coordinate==15)&&(gbCol_coordinate==0)))
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

void InitMaze2() 
{
//  PrintWall();
  gbCurrentRow_Coordinate=15;
  gbCurrentCol_Coordinate=0;
  InitOptimal();
//  PrintMaze();
//Always push row then column

  //Push everying around the CENTER!!
  push(6);
  push(6);
  push(7);
  push(6);
  push(8);
  push(6);
  push(9);
  push(6);

  push(6);
  push(9);
  push(7);
  push(9);
  push(8);
  push(9);
  push(9);
  push(9);
 
  push(6);
  push(7);
  push(9);
  push(7);
  push(6);
  push(8);
  push(9);
  push(8);

  
  while(stempty()==0)
  {
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
