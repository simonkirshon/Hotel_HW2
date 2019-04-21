#ifndef __EXPIRATION_H
#define __EXPIRATION_H

#define MONTHS_PER_YEAR 12
#define MINIMUM_YEAR_EX_DATE 2010
#define MAXIMUM_YEAR_EX_DATE 2020

typedef struct
{
	int month;
	int year;
} expirationDate_t;

#endif //!__EXPIRATION_H

