/// C file layout

/******************************************************************************
*
* @file     ReceiveBT.c
* @brief    This file will read bluetooth data from a saved file. Can be improved 
			by reading directly to the serial com port.
* @version  V1.00
* @date     19, February 2017
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

/*----------------------------------------------------------------------------
*
* Place function bodies here.
*
*----------------------------------------------------------------------------*/

void getSetData(void)
{
	// read from a file 
	// C:\Users\obama\Desktop\MicromouseBitBucket\Micromouse Local Repository\JC_FloodFill
	char buffer[1000];
	FILE *pFile;
	pFile = fopen("C:\\Users\\obama\\Desktop\\MicromouseBitBucket\\Micromouse Local Repository\\JC_FloodFill\\btData.txt", "r");
	
	if (!pFile){

		printf("Error : Couldn't Read the File\n");

		return 1;

	}
	while (fgets(buffer, 1000, pFile) != NULL){

		printf("%s", buffer);

	}
	printf("Success Reading from File\n");
	if (fclose(pFile) != 0)
		printf("Error : File Not Closed\n");
}