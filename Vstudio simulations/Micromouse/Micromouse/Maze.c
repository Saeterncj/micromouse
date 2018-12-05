/******************************************************************************
*
* @file     Maze.c
* @brief    Bit manipulation functions
* @version  V1.00
* @date     16, February 2017
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


/*----------------------------------------------------------------------------
*
* Define global variables that will be used by both this source file
* and by other source files here.
*	must add extern on System.h
*----------------------------------------------------------------------------*/
uint8_t Maze[MAX_RC_SIZE][MAX_RC_SIZE] = { 0 };
uint8_t Wall[MAX_RC_SIZE][MAX_RC_SIZE] = { 0 };
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

void initWall(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			if (column == 0) Wall[row][column] |= enWest;
			if (column == 15) Wall[row][column] |= enEast;
			if (row == 0) Wall[row][column] |= enNorth;
			if (row == 15) Wall[row][column] |= enSouth;
		}
	}
	Wall[15][0] |= enEast;
}
/*
The goal of this is to initialize a maze based on setting a desired goal. This will be useful when we change
a desired location for the mouse to explore that is unvisited. This way the mouse can explore the whole map. 
*/
void initGoalMaze(uint8_t row, uint8_t column)
{
	uint8_t ucRow, ucColumn;
	// initialize maze back to zero
	/*for (ucRow = 0; ucRow < MAX_RC_SIZE; ucRow++)
	{
		for (ucColumn = 0; ucColumn < MAX_RC_SIZE; ucColumn++)
		{
			Maze[ucRow][ucColumn] = 0;
		}
	}*/
	if (row == 15) row -= 2;
	pushRowColumn(row+1, column, false);
	display();
	int smallest;
	while (!stempty()) {
		popRegRowColumn(&gstRowColumn);
		if (!((gstRowColumn.cRow == row) && (gstRowColumn.cColumn == column)) )
		{
			smallest = smallestOpenNeighbor();
			if (Maze[gstRowColumn.cRow][gstRowColumn.cColumn] != smallest + 1)
			{
				Maze[gstRowColumn.cRow][gstRowColumn.cColumn] = smallest + 1;
				pushOpenNeighbors();
			}
		}
	}


}
void initMaze(void)
{
	pushRowColumn(7, 6, false);
	display();
	int smallest;
	while (!stempty()) {
		popRegRowColumn(&gstRowColumn);
		if (!(((gstRowColumn.cRow == 8) && (gstRowColumn.cColumn == 8)) ||
			((gstRowColumn.cRow == 8) && (gstRowColumn.cColumn == 7)) ||
			((gstRowColumn.cRow == 7) && (gstRowColumn.cColumn == 8)) ||
			((gstRowColumn.cRow == 7) && (gstRowColumn.cColumn == 7))))
		{
			smallest = smallestOpenNeighbor();
			if (Maze[gstRowColumn.cRow][gstRowColumn.cColumn] != smallest + 1)
			{
				Maze[gstRowColumn.cRow][gstRowColumn.cColumn] = smallest + 1;
				pushOpenNeighbors();
			}
		}
	}
	

}

void displayWall(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			printf("%3d ", Wall[row][column]);
		}
		printf("\n");
	}
}
/*
	Display walls of the maze from what the robot knows.  We pass in the robot current row and col so we can print
	its position in the maze. we also pass its cardinaldirection so we can represent which way the robot is facing.
	The goal row and col is used to print 'G' in the maze to represent where the robot is trying to traverse to.
*/
void displayRealWall(uint8_t currentRow, uint8_t currentCol, uint8_t goalRow, uint8_t goalCol, enum enCardinalDirection enDesiredState)
{
	uint8_t row, column;
	for (row = 0; row < 33; row++)
	{
		for (column = 0; column < 33; column++)
		{
			if ((row % 2 == 0) && (column % 2 == 0)) // print intersections of walls
			{
				printf("+");
			}
			else if ((row % 2 == 1) && (column % 2 == 0))	// prints the east and west walls
			{
				if ((Wall[row / 2][(column + 1) / 2] & enWest) || (Wall[row / 2][(column + 1) / 2 - 1] & enEast))
				{
					printf("|");
				}
				 else
				 {
					 printf(" ");
				 }
				
			}
			else if ((row % 2 == 0) && (column % 2 == 1)) // prints the north and south walls
			{
				//printf("--");
				if ((Wall[row / 2][(column) / 2] & enNorth) || (Wall[row / 2 - 1][(column) / 2] & enSouth))
				{
					printf("--");
				}
				else
				{
					printf("  ");
				}
			}
			else   // prints robot position and maze goal, otherwise print spaces
			{
				if (row / 2 == currentRow && (column) / 2 == currentCol)	// if iteration is at current robot location
				{
					if (enDesiredState == enNorth) { printf("^ "); }
					else if (enDesiredState == enEast) { printf("> "); }
					else if (enDesiredState == enSouth) { printf("v "); }
					else if (enDesiredState == enWest) { printf("< "); }
				}
				else if (row / 2 == goalRow && (column) / 2 == goalCol) {	// if iteration at robot goal
					printf("G ");
				}
				else
				{
					printf("  ");
				}
			}
			
		}
		printf("\n");
	}
}
/*
	displayRealwallNum prints the wall and in each cell, contains a number that represents its distance to the goal.
*/
void displayRealWallNum(void)
{
	uint8_t row, column;
	for (row = 0; row < 33; row++){
		for (column = 0; column < 33; column++){
			//printf("%3d ", Maze[row][column]);
			// if odd skip 
			if ((row % 2 == 0) && (column % 2 == 0)){
				printf("+");
			}
			else if ((row % 2 == 1) && (column % 2 == 0)){
				if ((Wall[row / 2][(column + 1) / 2] & enWest) || (Wall[row / 2][(column + 1) / 2 - 1] & enEast)){
					printf("|");
				}
				else{
					printf(" ");
				}

			}
			else if ((row % 2 == 0) && (column % 2 == 1)){
				//printf("--");
				if ((Wall[row / 2][(column) / 2] & enNorth) || (Wall[row / 2 - 1][(column) / 2] & enSouth)){
					printf("--");
				}
				else{
					printf("  ");
				}
			}
			else{
				if (Maze[row / 2][column / 2] / 10)
					printf("%d", Maze[row / 2][column / 2]);
				else
					printf(" %d", Maze[row / 2][column / 2]);
			}
		}
		printf("\n");
	}
}

void displayMaze(void)
{
	uint8_t row, column;
	for (row = 0; row < MAX_RC_SIZE; row++)
	{
		for (column = 0; column < MAX_RC_SIZE; column++)
		{
			printf("%3d ", Maze[row][column]);
		}
		printf("\n");
	}
}
