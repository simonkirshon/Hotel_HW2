#ifndef __HOTEL_H
#define __HOTEL_H

#include "room.h"

typedef struct
{
	int numFloors;
	int numRooms;
	room_t** roomMatrix;
} hotel_t;

void initHotel(hotel_t*  emptyHotel);
void showHotelStatus(const hotel_t hotel);
void displayRoomDetails(const hotel_t hotel, int room);

#endif //!__HOTEL_H