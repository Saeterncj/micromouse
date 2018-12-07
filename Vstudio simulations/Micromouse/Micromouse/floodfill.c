/// C file layout

/******************************************************************************
*
* @file     floodfill.c
* @brief    The purpose of this file is to simulate the flood fill algorithm to 
			solve the generated maze
* @version  n/a
* @date     26, Feb 2017
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
#include "Stack.h"
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
*
*----------------------------------------------------------------------------*/

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
static enum enCardinalDirection enDesiredState;
/*----------------------------------------------------------------------------
*
* Place function bodies here.
*

*----------------------------------------------------------------------------*/
void AdjacentWalls()//IF find wall look for adjacent cells to wall discoverd
{
	if (((GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn]&enNorth) == enNorth) && (gstRowColumn.cRow != 0)) {  //Includes boundaries!!!

		pushRowColumn(gstRowColumn.cRow - 1, gstRowColumn.cColumn, false);
		if (Wall[gstRowColumn.cRow - 1][gstRowColumn.cColumn]<16) // if not visited
		{
			Wall[gstRowColumn.cRow - 1][gstRowColumn.cColumn] |= 4;
		}
	}//push maze[row coordinate-1][gstRowColumn.cColumn]
	if ((GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn] &enEast) == enEast && (gstRowColumn.cColumn != 15)) {
		pushRowColumn(gstRowColumn.cRow, gstRowColumn.cColumn + 1,false);
		if (Wall[gstRowColumn.cRow][gstRowColumn.cColumn + 1]<16)
		{
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn + 1] |= 8;
		}
	} //push maze[row coordinate][ col coordinate+1]
	if ((GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn] &enSouth) == enSouth && (gstRowColumn.cRow != 15)) {
		pushRowColumn(gstRowColumn.cRow +1, gstRowColumn.cColumn, false);
		if (Wall[gstRowColumn.cRow + 1][gstRowColumn.cColumn]<16)
		{
			Wall[gstRowColumn.cRow + 1][gstRowColumn.cColumn] |= 1;
		}
	} //push maze[row coordinate+1][ col coordinate]
	if (((GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn] &enWest) == enWest) && (gstRowColumn.cColumn != 0)) {

		pushRowColumn(gstRowColumn.cRow, gstRowColumn.cColumn- 1, false);
		if (Wall[gstRowColumn.cRow][gstRowColumn.cColumn - 1]<16)
		{
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn - 1] |= 2;
		}
	}  //push maze[row coordinate][ col coordinate-1]

}
int smallestOpenNeighbor(void)
{
	uint8_t row = gstRowColumn.cRow;
	uint8_t col = gstRowColumn.cColumn;
	int smallest = 250;
	if (!(Wall[row][col] & enNorth)) 
	{
		if (smallest > Maze[row - 1 ][col])
		{
			smallest = Maze[row - 1][col];
			enDesiredState = enNorth;
		}

	}
	if (!(Wall[row][col] & enEast))
	{
		if (smallest > Maze[row ][col+1])
		{
			smallest = Maze[row ][col+1];
			enDesiredState = enEast;
		}

	}
	if (!(Wall[row][col] & enSouth))
	{
		if (smallest > Maze[row + 1][col])
		{
			smallest = Maze[row + 1][col];
			enDesiredState = enSouth;
		}
	}
	if (!(Wall[row][col] & enWest))
	{
		if (smallest > Maze[row][col - 1])
		{
			smallest = Maze[row][col - 1];
			enDesiredState = enWest;
		}
	}
	return smallest;

}

void pushOpenNeighbors(void) {
	uint8_t row = gstRowColumn.cRow;
	uint8_t col = gstRowColumn.cColumn;
	if (!(Wall[row][col] & enNorth))
	{
		pushRowColumn(row -  1, col, false);
	}
	if ( !(Wall[row][col] & enEast))
	{
		pushRowColumn(row, col+1, false);
	}
	if (!(Wall[row][col] & enSouth ))
	{
		pushRowColumn(row + 1, col, false);
	}
	if (!(Wall[row][col] & enWest))
	{
		pushRowColumn(row, col - 1, false);
	}

	// 
}
void floodFill(uint8_t DesiredRow, uint8_t DesiredCol,uint8_t initRow, uint8_t initCol)
{
	static uint8_t ucCurrentRow;
	static uint8_t ucCurrentColumn;
	uint8_t smallest;
	ucCurrentRow = initRow;
	ucCurrentColumn = initCol;
	gstRowColumn.cRow = initRow;
	gstRowColumn.cColumn = initCol;
	int runAuto, waitTime;
	printf("Do you want to run auto or iterate yourself?(1 for auto,0 for yourself)\n");
	scanf("%d", &runAuto);
	if (runAuto) {
		printf("Enter your delay for each iteration in millisecs.\n");
		scanf("%d", &waitTime);
	}
	//While not at center
	while (!((gstRowColumn.cRow == DesiredRow) && (gstRowColumn.cColumn == DesiredCol)))	// While not at goal
	{
		// If the Current wall is not visited, then check to see if there is wall to be learned
		if (!(Wall[gstRowColumn.cRow][gstRowColumn.cColumn] & enVisited))
		{
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] = GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn];
			Wall[gstRowColumn.cRow - 1][gstRowColumn.cColumn] |= (GeneratedWall[gstRowColumn.cRow - 1][gstRowColumn.cColumn] & enSouth);
			Wall[gstRowColumn.cRow + 1][gstRowColumn.cColumn] |= (GeneratedWall[gstRowColumn.cRow+1][gstRowColumn.cColumn] & enNorth);
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn- 1] |= (GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn - 1] & enEast);
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn + 1] |= (GeneratedWall[gstRowColumn.cRow][gstRowColumn.cColumn+ 1] & enWest);

			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] |= enVisited;
			pushRowColumn(gstRowColumn.cRow, gstRowColumn.cColumn, false);
			ucCurrentColumn = gstRowColumn.cColumn;
			ucCurrentRow = gstRowColumn.cRow;
			AdjacentWalls();

			while (stempty() == 0)
			{
				popRegRowColumn(&gstRowColumn);
				if (!((gstRowColumn.cRow == DesiredRow) && (gstRowColumn.cColumn == DesiredCol))) { // if not goal
					smallest = smallestOpenNeighbor();
					if (Maze[gstRowColumn.cRow][gstRowColumn.cColumn] != smallest + 1)
					{
						Maze[gstRowColumn.cRow][gstRowColumn.cColumn] = smallest + 1;
						pushOpenNeighbors();
						
					}
				}
			}
			gstRowColumn.cRow = ucCurrentRow;
			gstRowColumn.cColumn = ucCurrentColumn;
		}
		// move to the next minimum accesible cell
		smallestOpenNeighbor();
		
		if (enDesiredState == enNorth) { gstRowColumn.cRow--; }
		else if (enDesiredState == enEast) { gstRowColumn.cColumn++; }
		else if (enDesiredState == enSouth) { gstRowColumn.cRow++; }
		else if (enDesiredState == enWest) { gstRowColumn.cColumn--; }
		displayRealGeneratedWall(gstRowColumn.cRow, gstRowColumn.cColumn,DesiredRow, DesiredCol);
		displayRealWall(gstRowColumn.cRow, gstRowColumn.cColumn, DesiredRow, DesiredCol, enDesiredState);

		// if it is runAuto then we let it iterate with a delay of waitTime in milliseconds
		// else we wait for user to press enter for the next iteration.
		if (runAuto) wait(waitTime);
		else  getchar();
		system("CLS");
	}

}