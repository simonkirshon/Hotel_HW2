#pragma warning(disable: 4996 4710)

#include "hotel.h"
#include "room.h"
#include <stdio.h>
/*assuming the max number of rooms per floor is 100*/
void displayRoomDetails(const hotel_t hotel, int room)
{
	if ((hotel.roomMatrix[(room - 1) / MAX_ROOMS_PER_FLOOR][(room - 1) % MAX_ROOMS_PER_FLOOR].isFull))
		printf("In room %d: |Number of guests: %d| |Number of requested meals: %d|\n", room, hotel.roomMatrix[(room - 1) / MAX_ROOMS_PER_FLOOR][(room - 1) % MAX_ROOMS_PER_FLOOR].numGuests, hotel.roomMatrix[(room - 1) / MAX_ROOMS_PER_FLOOR][(room - 1) % MAX_ROOMS_PER_FLOOR].numRequestedMeals);
	else
		printf("Room is empty.\n");
}