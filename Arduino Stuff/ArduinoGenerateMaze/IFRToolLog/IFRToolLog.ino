//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(10, 11); // RX, TX

long countR,countL;
#define STACK_MAX_SIZE 100
#define MAX_RC_SIZE  16
enum enCardinalDirection
{
  enNorth = 0x01,
  enEast = 0x02,
  enSouth = 0x04,
  enWest = 0x08,
  enVisited = 0x10,
  enInStack = 0x20,
};
uint8_t GeneratedMaze[MAX_RC_SIZE][MAX_RC_SIZE] = {0};
uint8_t GeneratedWall[MAX_RC_SIZE][MAX_RC_SIZE] = {0};

struct Stack {
  uint8_t cRow[STACK_MAX_SIZE];
  uint8_t cColumn[STACK_MAX_SIZE];
  int iTop;
}stStack;
struct stRowColumn {
  unsigned char cRow;
  unsigned char cColumn;
}gstRowColumn;

void setup() {
  Serial.begin(115200);
  //mySerial.begin(115200);
  initStack();
  initGeneratedWall();
  GenerateWall();
  displayRealGeneratedWall();
  displayGeneratedWall();
}

void loop() {
  static uint8_t doneFlag = 0;

  if(!doneFlag)
  {
    for(int row = 0; row < 16; row++)
    {
      for(int column = 0; column < 16; column++)
      {
        //mySerial.write(
        Serial.print(row);
        Serial.print(",");
        Serial.print(column);
        Serial.print(",");
        Serial.print(GeneratedWall[row][column]%16);
        Serial.println("");
        delay(500);
      }
      
    }
    
  }
  //displayGeneratedWall();
  //delay(2000);
  
}

