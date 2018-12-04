/// C file layout

/******************************************************************************
*
* @file     GenerateMaze.c
* @brief    the object is to generate a solveable micromouse maze
* @version  V1.00
* @date     17, February 2017
*
* @note
*
******************************************************************************/


/*----------------------------------------------------------------------------
*
* Place #include files required to compile this source file here.
*
*----------------------------------------------------------------------------*/
#include "System.h"

/*----------------------------------------------------------------------------
*
* Place function prototypes that will be used only by this file here.
* This section need only include "forward referenced" functions.
*
*----------------------------------------------------------------------------*/
void checkForVisitedNeighbors(uint8_t row, uint8_t column);
void pushUnvisitedNeighbors(uint8_t row, uint8_t column);

/*----------------------------------------------------------------------------
*
* Define global variables that will be used by both this source file
* and by other source files here.
*
*----------------------------------------------------------------------------*/
uint8_t GeneratedMaze[MAX_RC_SIZE][MAX_RC_SIZE] = { 0 };
uint8_t GeneratedWall[MAX_RC_SIZE][MAX_RC_SIZE] = { 0 };
/*----------------------------------------------------------------------------
*
* Place #define constants and macros that will be used only by this
* source file here.
*
*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that will be used only
* by this source file here.
*
*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place static variables that will be used only by this file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place function bodies here.
*
*----------------------------------------------------------------------------*/

// Populate the Generated Wall
void initGeneratedWall(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			/*if (column == 0) GeneratedWall[row][column] |= enWest;
			if (column == 15) GeneratedWall[row][column] |= enEast;
			if (row == 0) GeneratedWall[row][column] |= enNorth;
			if (row == 15) GeneratedWall[row][column] |= enSouth;*/
			// A=10,B=11,C=12,D=13,E=14,F=15
			if (column == 0 && row == 15){ GeneratedWall[row][column] = 0x0E; }
			else if (column == 0 && row == 14)GeneratedWall[row][column] = 0x0B;
			else if (column == 1 && row == 15)GeneratedWall[row][column] = 0x0C;
			else {GeneratedWall[row][column] = 0x0F;}
			
		}

	}
	GeneratedWall[7][8] = 0x33;
	GeneratedWall[7][7] = 0x39;
	GeneratedWall[8][7] = 0x3c;
	GeneratedWall[8][8] = 0x36;
}

void GenerateWall(void)
{
	// Use recursive algorithm
	
	static uint8_t row, column;
	static uint8_t SelectRandomFrontier;
	//pushRowColumn(13, 0);
	//pushRowColumn(14, 1);
	//pushRowColumn(15, 2);
	pushRowColumn(6, 8);

	/*
		While there are frontiers,
			pop a random frontier
			check to see how many visited maze cell are connected with it,
			if there are more than one:
			then choose randomly which is going to be connected to it.
			update cell to be visited and push its unvisited neighbors.
			
	*/
	//printf("if empty: %d \n", stempty());
	uint8_t largest = 0;
	while (!stempty()) // while stack is not empy
	{
		// Select a random Frontier selected by randomly selecting an index;
		
		SelectRandomFrontier = rand() % (stStack.iTop + 1);
		// printf("%d \n", SelectRandomFrontier);
		printf("%d \n", largest);
		if (stStack.iTop > largest) largest = stStack.iTop;
		popIndex(&gstRowColumn, SelectRandomFrontier);
		checkForVisitedNeighbors(gstRowColumn.cRow,gstRowColumn.cColumn);
		pushUnvisitedNeighbors(gstRowColumn.cRow, gstRowColumn.cColumn);
		//displayRealGeneratedWall();
		//system("Pause");
		// Check to see if it has any visited cells are connected 

	}
	displayRealGeneratedWall();
	system("Pause");
	if ((GeneratedWall[15][0] & enEast) != enEast)
	{
		GeneratedWall[15][0] |= enEast;
		GeneratedWall[15][1] |= enWest;
		GeneratedWall[15][1] &= ~enNorth;
		GeneratedWall[15][0] &= ~enNorth;
		GeneratedWall[14][0] &= ~enEast;
		GeneratedWall[14][1] &= ~enWest;
		GeneratedWall[14][1] &= ~enSouth;
	}

}

void checkForVisitedNeighbors(uint8_t row, uint8_t column)
{
	uint8_t counter = 0;
	uint8_t wallToCheckFlags = 0x0F;
	uint8_t connectableWalls = 0;
	uint8_t randNum;
	uint8_t iterate = 0;
	if (row == 0) wallToCheckFlags &= ~(enNorth);
	if (column == 0) wallToCheckFlags &= ~(enWest);
	if (row == 15) wallToCheckFlags &= ~(enSouth);
	if (column == 15) wallToCheckFlags &= ~(enEast);
	if (row == 6 && (column == 7)) wallToCheckFlags &= ~(enSouth);
	if (column == 9 && (row == 7 || row == 8)) wallToCheckFlags &= ~(enWest);
	if (row == 9 && (column == 7 || column == 8)) wallToCheckFlags &= ~(enNorth);
	if (column == 6 && (row == 7 || row == 8)) wallToCheckFlags &= ~(enEast);

	if (wallToCheckFlags & enNorth)	// if we can check the cell north of us
	{
		if (GeneratedWall[row - 1][column] & enVisited){ 
			counter++; 
			connectableWalls |= enNorth; 
		}
	}
	if (wallToCheckFlags & enEast)	// if we can check the cell east of us
	{
		if (GeneratedWall[row][column + 1] & enVisited) {
			counter++; 
			connectableWalls |= enEast;
		}
	}
	if (wallToCheckFlags & enSouth)	// if we can check the cell south of us
	{
		if (GeneratedWall[row + 1][column] & enVisited) {
			counter++; 
			connectableWalls |= enSouth;
		}
	}
	if (wallToCheckFlags & enWest)	// if we can check the cell west of us
	{
		if (GeneratedWall[row][column - 1] & enVisited) {
			counter++;
			connectableWalls |= enWest;
		}
	}
	//printf("Number of counters %d \n", counter);
	//if counter == 0 then there is a problem
	if (counter) randNum = (rand() % (counter));
	
	while ((counter))
	{
		if (connectableWalls == 0)
		{
			printf("Error, there is no connectable Walls\n\n");
			break;
		}
		if (connectableWalls & (1 << iterate)){
			counter--;
			if (counter == randNum)
			{
				connectableWalls &= (1 << iterate);
				break;
			}
		}
		iterate++;

	}
	if (connectableWalls & enNorth)	// if we can check the cell north of us
	{
		GeneratedWall[row - 1][column] &= ~(enSouth);
		GeneratedWall[row][column] &= ~(enNorth);
	}
	else if (connectableWalls & enEast)	// if we can check the cell east of us
	{
		GeneratedWall[row][column+1] &= ~(enWest);
		GeneratedWall[row][column] &= ~(enEast);
	}
	else if (connectableWalls & enSouth)	// if we can check the cell south of us
	{
		GeneratedWall[row + 1][column] &= ~(enNorth);
		GeneratedWall[row][column] &= ~(enSouth);
	}
	else if (connectableWalls & enWest)	// if we can check the cell west of us
	{
		GeneratedWall[row][column - 1] &= ~(enEast);
		GeneratedWall[row][column] &= ~(enWest);
	}

	GeneratedWall[row][column] |= enVisited;


}

void pushUnvisitedNeighbors(uint8_t row, uint8_t column)
{
	//uint8_t counter = 0;
	uint8_t PushableWalls = 0x0F;
	uint8_t connectableWalls = 0;
	uint8_t randNum;
	if (row == 0) PushableWalls &= ~(enNorth);
	if (column == 0) PushableWalls &= ~(enWest);
	if (row == 15) PushableWalls &= ~(enSouth);
	if (column == 15) PushableWalls &= ~(enEast);

	if (PushableWalls & enNorth)	// if we can check the cell north of us
	{
		pushRowColumn(row - 1, column);
	}
	if (PushableWalls & enEast)	// if we can check the cell east of us
	{
		pushRowColumn(row , column + 1);
	}
	if (PushableWalls & enSouth)	// if we can check the cell south of us
	{
		pushRowColumn(row + 1, column);
	}
	if (PushableWalls & enWest)	// if we can check the cell west of us
	{
		pushRowColumn(row , column - 1);
	}

}

void displayRealGeneratedWall(void)
{
	uint8_t row, column;
	for (row = 0; row < 33; row++)
	{
		for (column = 0; column < 33; column++)
		{
			//printf("%3d ", Maze[row][column]);
			// if odd skip 
			if ((row % 2 == 0) && (column % 2 == 0))
			{
				printf("+");
			}
			else if ((row % 2 == 1) && (column % 2 == 0))
			{
				if ((GeneratedWall[row / 2][(column + 1) / 2] & enWest) || (GeneratedWall[row / 2][(column + 1) / 2 - 1] & enEast))
				{
					printf("|");
				}
				else
				{
					printf(" ");
				}


			}
			else if ((row % 2 == 0) && (column % 2 == 1))
			{
				//printf("--");
				if ((GeneratedWall[row / 2][(column) / 2] & enNorth) || (GeneratedWall[row / 2 - 1][(column) / 2] & enSouth))
				{
					printf("--");
				}
				else
				{
					printf("  ");
				}
			}
			else if ((row % 2 == 1) && (column % 2 == 1))	// comment this if statement out later
			{
				//printf("--");
				if ((GeneratedWall[row / 2][(column) / 2] & 0x10))	// part of the maze
				{
					//printf("v ");
					printf("  ");
				}
				else if ((GeneratedWall[row / 2][(column) / 2] & 0x20))	// part of the maze
				{
					//printf("s ");
					printf("  ");
				}
				else
				{
					printf("  ");
				}
			}
			else
			{
				printf("  ");
			}

		}
		printf("\n");
	}
}

void displayGeneratedWall(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			printf("%3d ", GeneratedWall[row][column]&0xF);
		}
		printf("\n");
	}
}