#define ROTATE_LEFT         1   
#define ROTATE_RIGHT        2
#define GO_STRAIGHT         3
#define ROTATE_180          4

#define NORTH             1
#define EAST              2
#define SOUTH             4
#define WEST              8
#define VISITED             16
uint8_t count_temp;

//This initialization needs to be updated 

void Initialize_Maze() //-----------------------------------------------   Initialize gaucMAZE  ---------------------------
{
  uint8_t cell_val=0; //values range from 0-255 the cell value
  int i,j;
  // Quadrant I
  for(i=ARRAY_SIZE/2-1;i>-1; i--){
    for(j=ARRAY_SIZE/2;j<ARRAY_SIZE;j++){      
      gaucMAZE[i][j]=cell_val;
      if(j==ARRAY_SIZE-1){
        cell_val=cell_val-(ARRAY_SIZE/2-2); 
      }
      else{
        cell_val++;
      } //else
    }//end  of for
  }//end of for

  cell_val=0;
  //QUADRANT II
  for(i=ARRAY_SIZE/2-1;i>-1; i--){
    for(j=ARRAY_SIZE/2-1;j>-1;j--){      
      gaucMAZE[i][j]=cell_val;
          
      if(j==0){
        cell_val=cell_val-(ARRAY_SIZE/2-2); 
      }
      else{
        cell_val++;
      } //else  
    }//end  of for
  }//end of for

  cell_val=0;
  //QUADRANT III
  for( i=ARRAY_SIZE/2;i<ARRAY_SIZE; i++){  
    for(j=ARRAY_SIZE/2-1;j>-1;j--){      
      gaucMAZE[i][j]=cell_val;
          
      if(j==0){
        cell_val=cell_val-(ARRAY_SIZE/2-2); 
      }
      else{
        cell_val++;
      } //else
    }//end  of for
  }//end of for
  
  cell_val=0;
  //QUADRANT IV
  for(i=ARRAY_SIZE/2;i<ARRAY_SIZE; i++){
    for(j=ARRAY_SIZE/2;j<ARRAY_SIZE;j++){      
      gaucMAZE[i][j]=cell_val;
          
      if(j==ARRAY_SIZE-1){
        cell_val=cell_val-(ARRAY_SIZE/2-2); 
      }
      else{
        cell_val++;
      } //else  
    }//end  of for
  }//end of for
  cell_val=0;
}

void Transverse()       //--------------------------Can do EXTREME Editing!!--------------
{//---Be sure to update position state.
  
  if(gbPosition_state==0) //if it was facing NORTH
  {
    if(gbDesired_state==0)//next coordinate is up north
    {
      MoveRobot(GO_STRAIGHT);
    }
    else if(gbDesired_state==1) //next coordinate is facing east
    {
      MoveRobot(ROTATE_RIGHT);
      //rotate right then go straight

    }
    else if(gbDesired_state==2) //next coordinate is facing south
    {
      //rotate 180 and go back
      MoveRobot(ROTATE_180);
     
    }
    else if(gbDesired_state==3) //next coordinate is facing west
    {
      MoveRobot(ROTATE_LEFT);
    }
  }
  else if(gbPosition_state==1)    //if it was facing EAST
  {
    if(gbDesired_state==0)//next coordinate is up north
    {
      MoveRobot(ROTATE_LEFT);

    }
    else if(gbDesired_state==1) //next coordinate is facing east
    {
      MoveRobot(GO_STRAIGHT);
    }
    else if(gbDesired_state==2) //next coordinate is facing south
    {
      //rotate right go straight 
      MoveRobot(ROTATE_RIGHT);
    }
    else if(gbDesired_state==3) //next coordinate is facing west
    {
      //rotate 180
      MoveRobot(ROTATE_180);
     
    }
  }
  else if(gbPosition_state==2)    //if it was facing SOUTH
  {
    if(gbDesired_state==0)//next coordinate is up north
    {
      //rotate 180
      MoveRobot(ROTATE_180);
      
    }
    else if(gbDesired_state==1) //next coordinate is facing east
    {
      MoveRobot(ROTATE_LEFT);

      
    }
    else if(gbDesired_state==2) //next coordinate is facing south
    {
      MoveRobot(GO_STRAIGHT);
    }
    else if(gbDesired_state==3) //next coordinate is facing west
    {
      //rotate right
      MoveRobot(ROTATE_RIGHT);
    }
  }
  else if(gbPosition_state==3)    //if it was facing WEST
  {
    if(gbDesired_state==0)//next coordinate is up north
    {
      MoveRobot(ROTATE_RIGHT);

    }
    else if(gbDesired_state==1) //next coordinate is facing east
    {
      //rotate 180
      MoveRobot(ROTATE_180);
      
    }
    else if(gbDesired_state==2) //next coordinate is facing south
    {
      MoveRobot(ROTATE_LEFT);

    }
    else if(gbDesired_state==3) //next coordinate is facing west
    {
      MoveRobot(GO_STRAIGHT);
    }
  }
}
void UpdateCurrentCoordinate()
{
  if (gbDesired_state==0){gbRow_coordinate--;gbPosition_state=0;}
  else if(gbDesired_state==1){gbCol_coordinate++;gbPosition_state=1;}
  else if(gbDesired_state==2){gbRow_coordinate++;gbPosition_state=2;}
  else if(gbDesired_state==3){gbCol_coordinate--;gbPosition_state=3;}
}

void Walls_value()
{
  if(gdLeft_IR<threshold){gdLeft_IR=1;}
  else{gdLeft_IR=0;}
  if((gdMiddle_left_IR<threshold) &&(gdMiddle_right_IR<threshold)){gdMiddle_left_IR=1;}
  else{gdMiddle_left_IR=0;}
  if(gdRight_IR<threshold){gdRight_IR=1;}
  else{gdRight_IR=0;}
  
  if(gbPosition_state==0) //facing north then update the walls accordingly
  {
    gbWall_val=gdLeft_IR*WEST+gdMiddle_left_IR*NORTH+gdRight_IR*EAST+VISITED;
  }
  else if(gbPosition_state==1)
  {
    gbWall_val=gdLeft_IR*NORTH+gdMiddle_left_IR*EAST+gdRight_IR*SOUTH+VISITED;
  }
  else if(gbPosition_state==2)
  {
    gbWall_val=gdLeft_IR*EAST+gdMiddle_left_IR*SOUTH+gdRight_IR*WEST+VISITED;
  }
  else if(gbPosition_state==3)
  {
    gbWall_val=gdLeft_IR*SOUTH+gdMiddle_left_IR*WEST+gdRight_IR*NORTH+VISITED;
  }
  gaucWALL[gbRow_coordinate][gbCol_coordinate]=gbWall_val;
}

void AdjacentWalls()//IF find wall look for adjacent cells to wall discoverd
{
  if(((gbWall_val&NORTH)==NORTH)&& (gbRow_coordinate!=0)){  //Includes boundaries!!!
    push(gbRow_coordinate-1);
    push(gbCol_coordinate);
    if(gaucWALL[gbRow_coordinate-1][gbCol_coordinate]<16)
    {
      gaucWALL[gbRow_coordinate-1][gbCol_coordinate]=4;
    }
  }//push maze[row coordinate-1][gbCol_coordinate]
  if((gbWall_val&EAST)==EAST&& (gbCol_coordinate!=15)){
    push(gbRow_coordinate);
    push(gbCol_coordinate+1);
    if(gaucWALL[gbRow_coordinate][gbCol_coordinate+1]<16)
    {
     gaucWALL[gbRow_coordinate][gbCol_coordinate+1]=8;
    }
  } //push maze[row coordinate][ col coordinate+1]
  if((gbWall_val&SOUTH)==SOUTH && (gbRow_coordinate!=15)){   
    push(gbRow_coordinate+1);
    push(gbCol_coordinate);
    if(gaucWALL[gbRow_coordinate+1][gbCol_coordinate]<16)
    {
      gaucWALL[gbRow_coordinate+1][gbCol_coordinate]=1;
    }
  } //push maze[row coordinate+1][ col coordinate]
  if(((gbWall_val&WEST)==WEST)&&(gbCol_coordinate!=0)){
    push(gbRow_coordinate);
    push(gbCol_coordinate-1);
    if(gaucWALL[gbRow_coordinate][gbCol_coordinate-1]<16)
    {
      gaucWALL[gbRow_coordinate][gbCol_coordinate-1]=2;
    }
  }  //push maze[row coordinate][ col coordinate-1]
  
}
void StackOpenNeighbors()
{
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&NORTH)!=NORTH)&& (gbRow_coordinate!=0)){    //open Wall on the north
    push(gbRow_coordinate-1);
    push(gbCol_coordinate);
  } //push maze[row coordinate-1][ col coordinate]
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&EAST)!=EAST)&&(gbCol_coordinate!=15)){      //Open walll on the east
    push(gbRow_coordinate);
    push(gbCol_coordinate+1);
  } //push maze[row coordinate][ col coordinate+1]
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&SOUTH)!=SOUTH)&&(gbRow_coordinate!=15)){    //Open wall on the south
    push(gbRow_coordinate+1);
    push(gbCol_coordinate);
  } //push maze[row coordinate+1][ col coordinate]
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&WEST)!=WEST) &&(gbCol_coordinate!=0)){      //Open wall on the West
    push(gbRow_coordinate);
    push(gbCol_coordinate-1) ;
  }  //push maze[row coordinate][ col coordinate-1]
}
void SmallestOpenNeighbors()
{
  byte temp[4];
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&NORTH)!=NORTH)&& (gbRow_coordinate!=0)){    //open Wall on the north
    temp[0]=gaucMAZE[gbRow_coordinate-1][gbCol_coordinate];
    } //push maze[row coordinate-1][ col coordinate]
    else{temp[0]=HIGH_VAL;}
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&EAST)!=EAST)&&(gbCol_coordinate!=15)){      //Open walll on the east
    temp[1]=gaucMAZE[gbRow_coordinate][gbCol_coordinate+1];
    } //push maze[row coordinate][ col coordinate+1]
    else{temp[1]=HIGH_VAL;}
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&SOUTH)!=SOUTH) && (gbRow_coordinate!=15)){    //Open wall on the south 
    temp[2]=gaucMAZE[gbRow_coordinate+1][gbCol_coordinate];
    } //push maze[row coordinate+1][ col coordinate]
    else{temp[2]=HIGH_VAL;}
  if(((gaucWALL[gbRow_coordinate][gbCol_coordinate]&WEST)!=WEST) &&(gbCol_coordinate!=0)){      //Open wall on the West
    temp[3]=gaucMAZE[gbRow_coordinate][gbCol_coordinate-1];
    }  //push maze[row coordinate][ col coordinate-1]
    else{temp[3]=HIGH_VAL;}

  gbSmallest=temp[0];
  for(count_temp=0;count_temp<4;count_temp++)
  {
    if(temp[count_temp]<gbSmallest)
    {
    gbSmallest=temp[count_temp];
    }
  }
  if(gbSmallest==temp[0]){ gbDesired_state=0;}
  else if(gbSmallest==temp[1]){ gbDesired_state=1;}
  else if(gbSmallest==temp[2]){ gbDesired_state=2;}
  else if(gbSmallest==temp[3]){ gbDesired_state=3;}
}

void SmallestOpenNeighbors1()
{
  byte temp[4];
  if(((gaucWALL[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate]&NORTH)!=NORTH)&& (gbCurrentRow_Coordinate!=0)){    //open Wall on the north
    temp[0]=gaucMAZE[gbCurrentRow_Coordinate-1][gbCurrentCol_Coordinate];
    } //push maze[row coordinate-1][ col coordinate]
    else{temp[0]=HIGH_VAL;}
  if(((gaucWALL[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate]&EAST)!=EAST)&&(gbCurrentCol_Coordinate!=15)){      //Open walll on the east
    temp[1]=gaucMAZE[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate+1];
    } //push maze[row coordinate][ col coordinate+1]
    else{temp[1]=HIGH_VAL;}
  if(((gaucWALL[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate]&SOUTH)!=SOUTH) && (gbCurrentRow_Coordinate!=15)){    //Open wall on the south 
    temp[2]=gaucMAZE[gbCurrentRow_Coordinate+1][gbCurrentCol_Coordinate];
    } //push maze[row coordinate+1][ col coordinate]
    else{temp[2]=HIGH_VAL;}
  if(((gaucWALL[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate]&WEST)!=WEST) &&(gbCurrentCol_Coordinate!=0)){      //Open wall on the West
    temp[3]=gaucMAZE[gbCurrentRow_Coordinate][gbCurrentCol_Coordinate-1];
    }  //push maze[row coordinate][ col coordinate-1]
    else{temp[3]=HIGH_VAL;}


  gbSmallest=temp[0];
  for(count_temp=0;count_temp<4;count_temp++)
  {
    if(temp[count_temp]<gbSmallest)
    {
    gbSmallest=temp[count_temp];
    }
  }
  if(gbSmallest==temp[0]){ gbDesired_state=0;}
  else if(gbSmallest==temp[1]){ gbDesired_state=1;}
  else if(gbSmallest==temp[2]){ gbDesired_state=2;}
  else if(gbSmallest==temp[3]){ gbDesired_state=3;}
}


int stfull() {
   if (st.top >= SIZE - 1)
   {
    Serial.println("Im FULLL!!!!!");
      return 1;
   }
      
   else
      return 0;
}
 
int push(int item) {
  if(stfull())
  {
    
  }
  else
  {
    st.top++;
    st.s[st.top] = item;
  }
}
int stempty() {
   if (st.top == -1)
      return 1;
   else
      return 0;
}
 
int pop() {
  int item;
  if(stempty())
  {
    Serial.println("Im empty");
  }
  else
  {
    item = st.s[st.top];
    st.top--;
  }
   
   
   return (item);
}
// 
void display() {
   int i;
   if (stempty())
      Serial.print("\nStack Is Empty!");
   else {
      for (i = st.top; i >= 0; i--)
         Serial.println(st.s[i]);
   }
}







