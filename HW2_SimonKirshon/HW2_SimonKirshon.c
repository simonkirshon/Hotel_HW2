#pragma warning(disable: 4996 4710)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "hotel.h"
#include "Main_Functions.h"
#include "reservation.h"
#include "room.h"


void main() {
	int i = 0, customerLogicSize = 0, customerPhysicalSize = STARTING_PHYSICAL_SIZE, reservationLogicSize = 0, reservationPhysicalSize = STARTING_PHYSICAL_SIZE, input;
	hotel_t hotel;
	printf("Creating hotel:\n");
	initHotel(&hotel);
	printf("Hotel has been created. \n");

	reservation_t* reservationList = (reservation_t*)malloc(sizeof(reservation_t)*reservationPhysicalSize);
	customer_t* customerList = (customer_t*)malloc(sizeof(customer_t)*customerPhysicalSize);

	if (!customerList || !reservationList) // (arr == NULL) --> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		exit(1);
	}

	do
	{
		displayMenu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("\n");
			showHotelStatus(hotel);
			break;
		case 2:
		{
			char name[MAX_NAME_LENGTH];
			char creditCard[MAX_CARD_LENGTH];
			int month = 0;
			int year = 0;
			char* customerName;
			char* customerCreditCard;
			expirationDate_t* expDate = (expirationDate_t*)malloc(sizeof(expirationDate_t));
			scanCustomerDetails(name, &customerName, creditCard, &customerCreditCard, &year, &month, expDate);
			addCustomer(&customerList, &customerPhysicalSize, &customerLogicSize, customerName, customerCreditCard, expDate);
			printf("Customer added.\n");
			break;
		}
		case 3:
			checkIn(&customerList, &customerPhysicalSize, &customerLogicSize, hotel, &reservationList, &reservationLogicSize, &reservationPhysicalSize);
			break;
		case 4:
			printf("\nEnter a room that you'd like to check-out: ");
			scanf("%d", &i);
			checkOut(hotel, &reservationList, reservationLogicSize, i);
			printf("Check-out to room %d completed", i);
			break;
		case 5:
			printf("\nEnter a room number: ");
			scanf("%d", &i);
			displayRoomDetails(hotel, i);
			break;
		case 6:
			printf("\nDisplaying customers before any change:\n");
			printCustomerList(customerList, customerLogicSize);
			printf("\nFixing all names to start with capital letters:\n");
			toUpperCase(customerList, customerLogicSize);
			printf("Success! Printing Customer array:\n");
			printCustomerList(customerList, customerLogicSize);
			break;
		case 7:
		{
			char subString[MAX_NAME_LENGTH];
			int subCustomerLogicSize = 0;
			printf("\nEnter a substring you'd like to search for: ");
			scanf("%s", subString);
			customer_t* subCustomers = hasSubString(subString, customerList, customerLogicSize, &subCustomerLogicSize);
			printf("All customers that have '%s' in their name are: \n", subString);
			printCustomerList(subCustomers, subCustomerLogicSize);

		}
		break;
		case -1:
			break;
		default:
			printf("Invalid option selected. Please try again.\n");
			break;
		}
	} while (input != -1);

	for (i = 0; i < customerLogicSize ; i++) {
	free(customerList[i].creditCard);
	free(customerList[i].cusName);
	free(customerList[i].expirationDate);
	}
	free(customerList);
	free(reservationList);
	for (i = 0; i < hotel.numFloors; i++)
		free(hotel.roomMatrix[i]);
	free(hotel.roomMatrix);
	system("pause");
}
