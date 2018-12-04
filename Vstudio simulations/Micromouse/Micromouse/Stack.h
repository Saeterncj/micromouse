
/* ----------------------------------------------------------------------------
@ file: Stack.h
Date Created: 2-14-17
Purpose: Header file for stack.c file.  Define functions, variables in this file
---------------------------------------------------------------------------- */
#ifndef Stack_h_
#define Stack_h_
/*----------------------------------------------------------------------------
*
* Include any additional header files that are needed to compile this
* header file here.
*
*----------------------------------------------------------------------------*/

#include "System.h"
/*-----------------------------------------------------------------------------
	Meaningful name that describes what is about to follow
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place #define constants and macros that are required for this header
* file or that need to be seen by more than one source file here.
*
*----------------------------------------------------------------------------*/

#define STACK_MAX_SIZE 1000

/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that need to be seen by
* multiple source files here.
*
*----------------------------------------------------------------------------*/

struct Stack {
	uint8_t cRow[STACK_MAX_SIZE];
	uint8_t cColumn[STACK_MAX_SIZE];
	int iTop;
} stStack;
struct stRowColumn {
	unsigned char cRow;
	unsigned char cColumn;
}gstRowColumn;

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

/*
		The following are for Stack.c
*/
void display();	
void popRowColumn(struct stRowColumn *pgstRowColumn);
void popRegRowColumn(struct stRowColumn *pgstRowColumn);
void pushRegRowColumn(int row, int column);
char stempty();
uint8_t stSize(void);
void popIndex(struct stRowColumn *pgstRowColumn, uint8_t index);
void pushRowColumn(int row, int column);
char isFull(); 
void initStack();
/*----------------------------------------------------------------------------
*
* End of file.
*
*----------------------------------------------------------------------------*/

#endif