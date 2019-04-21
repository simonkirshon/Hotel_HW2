#pragma warning(disable: 4996 4710)

#include "hotel.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>

void initHotel(hotel_t*  emptyHotel)
{
	int i, j;
	printf("Please choose number of floors: ");
	scanf("%d", &emptyHotel->numFloors);
	printf("Please choose number of rooms each floor (1-99): ");
	while ((emptyHotel->numRooms < 1) || (emptyHotel->numRooms >= MAX_ROOMS_PER_FLOOR)) {
		scanf("%d", &emptyHotel->numRooms);
		if (emptyHotel->numRooms < 1 || emptyHotel->numRooms >MAX_ROOMS_PER_FLOOR)
			printf("Number of rooms entered is not between 1 and 99. Try again: ");
	}
	emptyHotel->roomMatrix = (room_t**)malloc(sizeof(room_t*)*emptyHotel->numFloors);
	if (!(emptyHotel->roomMatrix)) // (arr == NULL) --> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		exit(1);
	}
	for (i = 0; i < emptyHotel->numFloors; i++) {
		emptyHotel->roomMatrix[i] = (room_t*)malloc(sizeof(room_t)*emptyHotel->numRooms);
		for (j = 0; j < emptyHotel->numRooms; j++)
			(emptyHotel->roomMatrix[i][j]).isFull = 0;
	}
}

void showHotelStatus(const hotel_t hotel)
{
	int i, j;
	for (i = 0; i < hotel.numFloors; i++)
	{
		for (j = 0; j < hotel.numRooms; j++)
		{
			if (j%hotel.numRooms == 0)
			{
				printf("Floor %3d:\n", i);
			}
			if (j + 1<10)
				printf("    Room %d0%d: ", i, j + 1);
			else
				printf("    Room %d%d: ", i, j + 1);
			if (hotel.roomMatrix[i][j].isFull)
			{
				printf("|Number of guests: %d| |Number of requested meals: %d|", hotel.roomMatrix[i][j].numGuests, hotel.roomMatrix[i][j].numRequestedMeals);
			}
			else {
				printf("Room is empty.");
			}
			printf("\n");
		}
	}
}