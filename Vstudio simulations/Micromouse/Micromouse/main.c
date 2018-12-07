#include <stdio.h>
#include "Stack.h"
#include "System.h"
#include <time.h>

void wait(unsigned timeout)
{
	timeout += clock();
	while (clock() < timeout) continue;
}

int main(void)
{
	
	//gstRowColumn;
	uint8_t ucDesiredRow = 8, ucDesiredCol = 8;
	uint8_t ucCurrentRow = 15, ucCurrentCol = 0;
	uint8_t ucRow, ucColumn;
	srand(time(NULL));
	initStack();	// init stack for generating wall 
	initWall();		// init our robot walls so it has empty wall except the boundaries
	initGeneratedWall();	// init generated wall to have walls on all cells
	GenerateWall();			// generate the whole maze
	displayRealGeneratedWall(ucCurrentRow, ucCurrentCol, ucDesiredRow, ucDesiredCol);	// display the solvable maze that was generated
	printf("Press Enter:\n");
	getchar();
	//system("Pause");

	printf("These values represent the robot current knowledge of the maze using bitmap\n");
	displayWall();
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	printf("These values represent the true distance of each cell to the goal\n");
	displayMaze();



	initStack();
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	//displayMaze();
	//displayRealWall();
	printf("Display of the true distance of each cell given the knew knowledge the robot learned\n");
	displayRealWallNum();
	printf("Press Enter:\n");
	getchar();
	//system("Pause");

	// **********************************************************
	for (ucRow = 0; ucRow < MAX_RC_SIZE; ucRow++)
	{
		for (ucColumn = 0; ucColumn < MAX_RC_SIZE; ucColumn++)
		{
			Maze[ucRow][ucColumn] = 0;
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] &= (~enVisited);
		}
	}
	initStack();
	ucCurrentCol = ucDesiredCol;
	ucCurrentRow = ucDesiredRow;
	ucDesiredRow = 15;
	ucDesiredCol = 15;
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	displayMaze();
	//displayRealWall();
	displayRealWallNum();
	printf("Press Enter:\n");
	getchar();
	//system("Pause");
	
	// **********************************************************
	for (ucRow = 0; ucRow < MAX_RC_SIZE; ucRow++)
	{
		for (ucColumn = 0; ucColumn < MAX_RC_SIZE; ucColumn++)
		{
			Maze[ucRow][ucColumn] = 0;
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] &= (~enVisited);
		}
	}
	initStack();
	ucCurrentCol = ucDesiredCol;
	ucCurrentRow = ucDesiredRow;
	ucDesiredRow = 0;
	ucDesiredCol = 0;
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	displayMaze();
	//displayRealWall();
	displayRealWallNum();
	printf("Press Enter:\n");
	getchar();
	//system("Pause");
	// **********************************************************
	for (ucRow = 0; ucRow < MAX_RC_SIZE; ucRow++)
	{
		for (ucColumn = 0; ucColumn < MAX_RC_SIZE; ucColumn++)
		{
			Maze[ucRow][ucColumn] = 0;
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] &= (~enVisited);
		}
	}
	initStack();
	ucCurrentCol = ucDesiredCol;
	ucCurrentRow = ucDesiredRow;
	ucDesiredRow = 15;
	ucDesiredCol = 0;
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	displayMaze();
	//displayRealWall();
	displayRealWallNum();
	printf("Press Enter:\n");
	getchar();
	//system("Pause");

	// **********************************************************
	for (ucRow = 0; ucRow < MAX_RC_SIZE; ucRow++)
	{
		for (ucColumn = 0; ucColumn < MAX_RC_SIZE; ucColumn++)
		{
			Maze[ucRow][ucColumn] = 0;
			Wall[gstRowColumn.cRow][gstRowColumn.cColumn] &= (~enVisited);
		}
	}
	initStack();
	ucCurrentCol = ucDesiredCol;
	ucCurrentRow = ucDesiredRow;
	ucDesiredRow = 7;
	ucDesiredCol = 7;
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	displayRealWallNum();
	//displayRealWall();
	//system("Pause");
	printf("Press Enter:\n");
	getchar();
	
	printf(" Im in here for now\n");
	printf("current Row: %d \t Current Col: %d\n\n", ucCurrentRow, ucCurrentCol);
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	printf(" I never got here\n");
	displayMaze();
	displayRealWallNum();
	//displayRealWall();
	//system("Pause");
	printf("Press Enter:\n");
	getchar();
}
