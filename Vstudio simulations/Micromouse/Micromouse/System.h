/* ----------------------------------------------------------------------------
@ file: System.h
Date Created: 2-14-17
Purpose: Header file for the whole system. For anything that will be used 
		in multiple files should be here.
---------------------------------------------------------------------------- */

#ifndef System_h_
#define System_h_
/* ----------------------------------------------------------------------------
	defining essential stuff
---------------------------------------------------------------------------- */
#define MAX_RC_SIZE	16
typedef unsigned char uint8_t;

/* ----------------------------------------------------------------------------
	Place global variables here
---------------------------------------------------------------------------- */
// uint8_t MAZE[MaxNumOfRows][MaxNumOfRows] = { 0 };
extern uint8_t Maze[MAX_RC_SIZE][MAX_RC_SIZE];
extern uint8_t Wall[MAX_RC_SIZE][MAX_RC_SIZE];

extern uint8_t GeneratedMaze[MAX_RC_SIZE][MAX_RC_SIZE];
extern uint8_t GeneratedWall[MAX_RC_SIZE][MAX_RC_SIZE];

typedef enum { false, true } bool;
enum enCardinalDirection
{
	enNorth = 0x01,
	enEast = 0x02,
	enSouth = 0x04,
	enWest = 0x08,
	enAllWall = 0x0F,
	enVisited = 0x10,
	enInStack = 0x20,
};

/*----------------------------------------------------------------------------
*
* Include any additional header files that are needed to compile this
* header file here.
*
*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Stack.h"
/*-----------------------------------------------------------------------------
Meaningful name that describes what is about to follow
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place #define constants and macros that are required for this header
* file or that need to be seen by more than one source file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that need to be seen by
* multiple source files here.
*
*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place global variables that are used by multiple source files here.
*
*----------------------------------------------------------------------------*/
// extern 
/*----------------------------------------------------------------------------
*
* Place function prototypes that need to be seen by multiple source files here.
*
*----------------------------------------------------------------------------*/

// ReturnedDataType functionName(ParametersDataType)
void initWall(void);
void initMaze(void);
void initGoalMaze(uint8_t row, uint8_t column);
void displayWall(void);
void displayMaze(void);
void displayRealWall(uint8_t, uint8_t, uint8_t, uint8_t, enum enCardinalDirection);
void displayRealWallNum(void);
void initGeneratedWall(void);
void GenerateWall(void);
void displayGeneratedWall(void);
void displayRealGeneratedWall(uint8_t, uint8_t, uint8_t, uint8_t);
int smallestOpenNeighbor(void);
void pushOpenNeighbors(void);
void floodFill(uint8_t DesiredRow, uint8_t DesiredCol, uint8_t initRow, uint8_t initCol);
void AdjacentWalls();
/*----------------------------------------------------------------------------
*
* End of file.
*
*----------------------------------------------------------------------------*/
#endif