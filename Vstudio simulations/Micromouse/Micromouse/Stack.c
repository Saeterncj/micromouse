/* ----------------------------------------------------------------------------
@ file: Stack.h
Date Created: 2-14-17
Purpose: Header file for stack.c file.  Define functions, variables in this file
---------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 Include necessary header files here
---------------------------------------------------------------------------- */
#include "Stack.h"

/* ----------------------------------------------------------------------------
	define global variable that will be used by this file and other files
---------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
	define static variable that will be used by this file only
---------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
	place functions that will be used in this file and other files here
---------------------------------------------------------------------------- */
void initStack()
{
	stStack.iTop = -1;
}
char isFull() {
	if (stStack.iTop >= STACK_MAX_SIZE - 1)
		return 1;	// it is full
	else
		return 0;	// 
}
/*
	// Pushing is different when generating wall
*/
void pushRowColumn(int row, int column,bool isGeneratingWall) {
	//stStack.iTop++;
	if (isFull())
	{
		// if full return nothing 
	}
	else
	{
		if (GeneratedWall[row][column] & enInStack && isGeneratingWall)
		{
			//if it is already in the stack, dont push it.
			//printf(" im in stack already \n");
		}
		else
		{
			stStack.cRow[++stStack.iTop] = row;
			stStack.cColumn[stStack.iTop] = column;
			//printf("pushing \n");
		}
	}
	if(isGeneratingWall)
		GeneratedWall[row][column] |= enInStack;
	else
		Wall[row][column] |= enInStack;
	//Set its push bit.
}
char stempty() {
	if (stStack.iTop == -1)
		return 1;
	else
		return 0;
}
/* pass in address of global struct to represent current row and column
then store the row and column in it.  This can merge into one with reg
*/
void popRegRowColumn(struct stRowColumn *pgstRowColumn) {
	if (stempty())
	{
		// cant pop is theres nothing
	}
	else
	{
		(*pgstRowColumn).cRow = stStack.cRow[stStack.iTop]; // Two different ways of accessing
															// pgstRowColumn->cRow = stStack.cRow[stStack.iTop];
		pgstRowColumn->cColumn = stStack.cColumn[stStack.iTop];
		Wall[stStack.cRow[stStack.iTop]][stStack.cColumn[stStack.iTop]] &= (~enInStack);
		stStack.iTop--;
	}

}
// 
void display() {
	int i;
	if (stempty())
		printf("\nStack Is Empty!");
	else {
		for (i = stStack.iTop; i >= 0; i--)
		{
			printf("Row: %d, Column %d \n", stStack.cRow[i], stStack.cColumn[i]);
		}
			
	}
}

uint8_t stSize(void)
{
	return stStack.iTop + 1;
}
void popIndex(struct stRowColumn *pgstRowColumn,uint8_t index) {
	if (stempty())
	{
		// cant pop is theres nothing
	}
	else if (index <= stStack.iTop)
	{
		(*pgstRowColumn).cRow = stStack.cRow[index]; // Two different ways of accessing
		// pgstRowColumn->cRow = stStack.cRow[stStack.iTop];
		pgstRowColumn->cColumn = stStack.cColumn[index];
		//unset the wall that its not in stack

		//GeneratedWall[stStack.cRow[index]][stStack.cColumn[index]] &= (~enInStack);

		uint8_t iterate;
		for (iterate = index; iterate < stStack.iTop; iterate++)
		{
			stStack.cRow[iterate] = stStack.cRow[iterate + 1];
			stStack.cColumn[iterate] = stStack.cColumn[iterate + 1];
		}
		stStack.iTop--;
	}

	//dont do nothing if index is to big
}
