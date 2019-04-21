#pragma warning(disable: 4996 4710)

#include "Main_Functions.h"
#include <stdio.h>

/*Prints menu*/
void displayMenu()
{
	printf("\nDisplaying functions:\n[1]: Show hotel status.\n[2]: Add a new customer.\n[3]: Check-in a customer.\n[4]: Check-out a customer.\n[5]: Show room's status.\n[6]: Change customer names to start with a capital letter. \n[7]: Find customer names with the same substring. \n[-1]: Exit.\nPlease choose a function: ");
	getchar();
}
