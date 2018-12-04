#include <stdio.h>
#include "Stack.h"
#include "System.h"



int main(void)
{
	
	//gstRowColumn;
	uint8_t ucDesiredRow = 8, ucDesiredCol = 8;
	uint8_t ucCurrentRow = 15, ucCurrentCol = 0;
	uint8_t ucRow, ucColumn;
	srand(time(NULL));
	initStack();
	initWall();
	initGeneratedWall();
	GenerateWall();


	displayRealGeneratedWall();
	displayGeneratedWall();
	system("Pause");



	displayWall();
	displayRealWall();
	initGoalMaze(ucDesiredRow, ucDesiredCol);
	displayMaze();



	initStack();
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	displayMaze();
	//displayRealWall();
	displayRealWallNum();
	system("Pause");

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
	system("Pause");
	
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
	system("Pause");
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
	system("Pause");

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
	displayRealWall();
	system("Pause");
	
	printf(" Im in here for now\n");
	printf("current Row: %d \t Current Col: %d\n\n", ucCurrentRow, ucCurrentCol);
	floodFill(ucDesiredRow, ucDesiredCol, ucCurrentRow, ucCurrentCol);
	printf(" I never got here\n");
	displayMaze();
	displayRealWallNum();
	displayRealWall();
	system("Pause");



}
