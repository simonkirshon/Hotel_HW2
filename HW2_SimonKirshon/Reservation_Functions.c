#pragma warning(disable: 4996 4710)

#include "reservation.h"
#include "customer.h"
#include "hotel.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>


void checkIn(customer_t** custList, int* cusPhysSize, int* cusLogicSize, hotel_t hotel, reservation_t** resList, int* resLogicSize, int* resPhysSize)
{
	reservation_t newReservation;
	int input, i, j, flag = 1, roomFound = 0;
	printf("Check in menu:\n\nDisplaying customers' names: \n");
	for (i = 0; i < *cusLogicSize; i++)
	{
		printf("[%d]: Customer name: %s\n", i + 1, (*custList)[i].cusName);
	}
	printf("Please choose a number between 1 to %d to select a customer that you'd like to check in.\nIf customer does not appear in list, press 0 to add a new one: ", (*cusLogicSize));

	do
	{
		while (getchar() != '\n') {}
		scanf("%d", &input);

		if (input >= 0 && input <= *cusLogicSize)
		{
			if (input == 0)
			{
				/*Adding a new customer on input == 0*/
				char name[MAX_NAME_LENGTH];
				char creditCard[MAX_CARD_LENGTH];
				int month = 0;
				int year = 0;
				char* customerName;
				char* customerCreditCard;
				expirationDate_t expDate;
				scanCustomerDetails(name, &customerName, creditCard, &customerCreditCard, &year, &month, &expDate);
				addCustomer(custList, cusPhysSize, cusLogicSize, customerName, customerCreditCard, &expDate);
				input = *cusLogicSize;
			}
			newReservation.customer = &((*custList)[input - 1]);
			printf("Please enter number of guests: ");
			/*Number of guests validation*/
			do {
				scanf("%d", &(newReservation.numOfguests));
				if (newReservation.numOfguests < 0 || newReservation.numOfguests > MAX_GUESTS)
					printf("Wrong input. Number of guests has to be between 1 and %d. try again: ", MAX_GUESTS);
			} while (newReservation.numOfguests < 0 || newReservation.numOfguests > MAX_GUESTS);

			printf("Please enter number of meals: ");
			/*Number of meals validation*/
			do {
				scanf("%d", &(newReservation.numRequstedMeals));
				if (newReservation.numRequstedMeals < 0 || newReservation.numRequstedMeals > newReservation.numOfguests)
					printf("Wrong input. Number of guests has to be between 0 and %d. try again: ", newReservation.numOfguests);
			} while (newReservation.numRequstedMeals < 0 || newReservation.numRequstedMeals > newReservation.numOfguests);
			newReservation.isCheckedOut = 0;
			/*Checking if a room is available*/
			for (i = 0; (i < hotel.numFloors) && roomFound == 0; i++)
			{
				for (j = 0; (j < hotel.numRooms) && roomFound == 0; j++)
				{
					if (!hotel.roomMatrix[i][j].isFull)
					{
						if (*resPhysSize == *resLogicSize)
						{
							*resPhysSize *= 2;
							*resList = (reservation_t*)realloc(*resList, *resPhysSize * sizeof(reservation_t));
							if (!(custList)) // (arr == NULL) --> allocaton didn't succeed
							{
								printf("ERROR! Out of memory!\n");
								exit(1);
							}
						}
						newReservation.room = &(hotel.roomMatrix[i][j]);
						(*resList)[(*resLogicSize)++] = newReservation;
						hotel.roomMatrix[i][j].numGuests = newReservation.numOfguests;
						hotel.roomMatrix[i][j].numRequestedMeals = newReservation.numRequstedMeals;
						hotel.roomMatrix[i][j].isFull = 1;
						roomFound = 1;
						break;
					}
					if (roomFound == 1) break;
				}
				if (roomFound == 0) printf("The hotel is full.");
				else printf("\nReservation completed. Selected room: Floor: %d, Room: %d\n", i, j + 1);
				flag = 0;
			}
		}
		else
		{
			printf("Wrong input. Please try again: ");
		}
	} while (flag);
}
/*Finds the address of the room in both hotel matrix and reservation array*/
void checkOut(hotel_t hotel, reservation_t** resList, int resLogicSize, int roomNumber)
{
	int i;
	room_t* roomAdd = &(hotel.roomMatrix[(roomNumber - 1) / MAX_ROOMS_PER_FLOOR][(roomNumber - 1) % MAX_ROOMS_PER_FLOOR]);
	for (i = 0; i < resLogicSize; i++)
	{
		if ((*resList)[i].room == roomAdd)
		{
			(*(*resList)[i].room).isFull = 0;
			(*resList)[i].isCheckedOut = 1;
		}
	}
}
