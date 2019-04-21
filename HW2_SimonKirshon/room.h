#ifndef __ROOM_H
#define __ROOM_H

#define MAX_ROOMS_PER_FLOOR 100


typedef struct
{
	int isFull;
	int numGuests;
	int numRequestedMeals;
} room_t;



#endif //!__ROOM_H
