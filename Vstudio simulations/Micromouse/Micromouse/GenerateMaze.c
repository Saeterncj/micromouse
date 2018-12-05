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

/*	-------------------------------------------------------
	Initilaize GeneratedWall[][] to have all four walls(north,east,south,west)
	except the goal(the middle four cell) and the beginning cell. 
	------------------------------------------------------- 
*/
void initGeneratedWall(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			//init all cell to have all four walls 
			GeneratedWall[row][column] = enAllWall;
		}
	}
	//*--*
	//|  |
	//*  *
	//|  |
	//*--*  bottom left 
	GeneratedWall[15][0] = 0x0E;
	GeneratedWall[14][0] = 0x0B;
	//*--*--*
	//|     |
	//*  *  *
	//|     |
	//*--*--*  Middle 4 cells
	GeneratedWall[7][8] = 0x33;
	GeneratedWall[7][7] = 0x39;
	GeneratedWall[8][7] = 0x3c;
	GeneratedWall[8][8] = 0x36;
}
/*	-------------------------------------------------------
	The GenerateWall generates a solvable micromouse maze the size of 16x16
	in GeneratedWall[][].  
	------------------------------------------------------*/	
void GenerateWall(void)
{
	static uint8_t row, column;
	static uint8_t SelectRandomFrontier;
	pushRowColumn(6, 8,true);
	uint8_t largest = 0;
	/*
		While there are frontiers,
		pop a random frontier
		check to see how many visited maze cell are connected with it,
		if there are more than one:
		then choose randomly which is going to be connected to it.
		update cell to be visited and push its unvisited neighbors.
	*/
	while (!stempty()) // while stack is not empy
	{
		// Select a random Frontier selected by randomly selecting an index;
		SelectRandomFrontier = rand() % (stStack.iTop + 1);
		//printf("%d \n", SelectRandomFrontier);
		//printf("%d \n", largest);
		if (stStack.iTop > largest) largest = stStack.iTop;
		popIndex(&gstRowColumn, SelectRandomFrontier);
		checkForVisitedNeighbors(gstRowColumn.cRow,gstRowColumn.cColumn);
		pushUnvisitedNeighbors(gstRowColumn.cRow, gstRowColumn.cColumn);
		//displayRealGeneratedWall();
		//system("Pause");
	}
	//*--*--* convert	*--*--*
	//|  |  |    to		|     | 
	//*--*--*--  ->		*  *  *--
	//|					|  |
	//*--*--*--			*--*--*--
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
	uint8_t wallToCheckFlags = enAllWall;
	uint8_t connectableWalls = 0;
	uint8_t randNum;
	uint8_t iterate = 0;
	if (row == 0) wallToCheckFlags &= ~(enNorth);
	if (column == 0) wallToCheckFlags &= ~(enWest);
	if (row == 15) wallToCheckFlags &= ~(enSouth);
	if (column == 15) wallToCheckFlags &= ~(enEast);
	if (row == 6 && (column == 7)) wallToCheckFlags &= ~(enSouth);
	if ((row == 7 || row == 8) && column == 9 ) wallToCheckFlags &= ~(enWest);
	if (row == 9 && (column == 7 || column == 8)) wallToCheckFlags &= ~(enNorth);
	if ((row == 7 || row == 8) && column == 6) wallToCheckFlags &= ~(enEast);

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
	uint8_t PushableWalls = enAllWall;
	uint8_t connectableWalls = 0;
	uint8_t randNum;
	if (row == 0) PushableWalls &= ~(enNorth);
	if (column == 0) PushableWalls &= ~(enWest);
	if (row == 15) PushableWalls &= ~(enSouth);
	if (column == 15) PushableWalls &= ~(enEast);

	if (PushableWalls & enNorth)	// if we can check the cell north of us
	{
		pushRowColumn(row - 1, column, true);
	}
	if (PushableWalls & enEast)	// if we can check the cell east of us
	{
		pushRowColumn(row , column + 1, true);
	}
	if (PushableWalls & enSouth)	// if we can check the cell south of us
	{
		pushRowColumn(row + 1, column, true);
	}
	if (PushableWalls & enWest)	// if we can check the cell west of us
	{
		pushRowColumn(row , column - 1, true);
	}

}

void displayRealGeneratedWall(uint8_t currentRow, uint8_t currentCol, uint8_t goalRow, uint8_t goalCol)
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
				if (row / 2 == currentRow && (column) / 2 == currentCol)	// if iteration is at current robot location
				{
					printf("x ");
				}
				else if (row / 2 == goalRow && (column) / 2 == goalCol) {	// if iteration at robot goal
					printf("G ");
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