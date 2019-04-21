#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include "expirationDate.h"

#define MAX_NAME_LENGTH 50
#define MAX_CARD_LENGTH 50
#define CREDIT_CARD_LENGTH 12

typedef struct
{
	int sysLogicNum;
	char* cusName;
	char* creditCard;
	expirationDate_t* expirationDate;
} customer_t;

void addCustomer(customer_t** customerList, int* customerPhysicalSize, int* customerLogicSize, char* name, char* creditCard, expirationDate_t* expDate);
void toUpperCase(customer_t* customerList, int customerLogicSize);
void nameToUpperCase(char name[]);
void scanCustomerDetails(char name[], char** customerName, char creditCard[], char** customerCreditCard, int* year, int* month, expirationDate_t* expDate);
void validCard(char* card);
void validDate(int* year, int* month);
customer_t* hasSubString(char subString[], customer_t* customerList, int size, int* newSize);
void printCustomerList(customer_t* customerList, int logicSize);

#endif //!__CUSTOMER_H