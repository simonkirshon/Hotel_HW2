#ifndef __RESERVATION_H
#define __RESERVATION_H

#include "customer.h"
#include "room.h"
#include "hotel.h"

#define MAX_GUESTS 4

typedef struct
{
	customer_t* customer;
	int numOfguests;
	int numRequstedMeals;
	room_t* room;
	int isCheckedOut;
} reservation_t;

void checkIn(customer_t** custList, int* cusPhysSize, int* cusLogicSize, hotel_t hotel, reservation_t** resList, int* resLogicSize, int* resPhysSize);
void checkOut(hotel_t hotel, reservation_t** resList, int resLogicSize, int roomNumber);

#endif //!__RESERVATION_H
