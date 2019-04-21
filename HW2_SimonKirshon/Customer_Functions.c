#pragma warning(disable: 4996 4710)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"


void addCustomer(customer_t** custList, int* cusPhysSize, int* cusLogicSize, char* name, char* creditCard, expirationDate_t* expDate)
{
	customer_t* newCustomer = (customer_t*)malloc(sizeof(customer_t));
	if (*cusPhysSize == *cusLogicSize)
	{
		*cusPhysSize *= 2;
		*custList = (customer_t*)realloc(*custList, *cusPhysSize * sizeof(customer_t));
		if (!(custList)) // (arr == NULL) --> allocaton didn't succeed
		{
			printf("ERROR! Out of memory!\n");
			exit(1);
		}
	}
	(*newCustomer).sysLogicNum = (*cusLogicSize) + 1;
	(*newCustomer).cusName = name;
	(*newCustomer).creditCard = creditCard;
	(*newCustomer).expirationDate = expDate;
	(*custList)[(*cusLogicSize)++] = *newCustomer;
	free(newCustomer);
}
void toUpperCase(customer_t* custList, int cusLogicSize)
{
	int i;
	for (i = 0; i < cusLogicSize; i++)
	{
		nameToUpperCase(custList[i].cusName);
	}
}

void nameToUpperCase(char name[])
{
	char lowerCase = *name;
	if (lowerCase >= 'a' && lowerCase <= 'z')
	{
		lowerCase = lowerCase - 'z' + 'Z';
		*name = lowerCase;
	}
}
void scanCustomerDetails(char* name, char** customerName, char creditCard[], char** customerCreditCard, int* year, int* month, expirationDate_t* expDate)
{
	getchar();
	printf("\nEnter a name: ");
	gets(name);
	*customerName = (char*)calloc(strlen(name) + 1, sizeof(char));
	strcpy(*customerName, name);
	*customerCreditCard = (char*)calloc(strlen(creditCard) + 1, sizeof(char));
	validCard(creditCard);
	strcpy(*customerCreditCard, creditCard);
	validDate(year, month);
	(*expDate).year = *year;
	(*expDate).month = *month;
}
/*Makes sure credit card consists of 12 digits*/
void validCard(char* card)
{
	printf("Enter the credit card number:\n");
	int isValid = 1, i;
	do
	{
		isValid = 1;
		gets(card);
		for (i = 0; i < CREDIT_CARD_LENGTH; i++)
		{
			if (card[i] < '0' || card[i] > '9')
			{
				isValid = 0;
				i = CREDIT_CARD_LENGTH;
				printf("Invalid Credit Card! Try again:\n");
			}
		}
		if (strlen(card) != 12)
			isValid = 0;
	} while (isValid == 0);
}
void validDate(int* year, int* month)
{
	do
	{
		printf("Enter the credit card expiration Year: \n");
		scanf("%d", year);
		if (*year > MAXIMUM_YEAR_EX_DATE || *year < MINIMUM_YEAR_EX_DATE)
			printf("Valid credit card year is between %d and %d.\n", MINIMUM_YEAR_EX_DATE, MAXIMUM_YEAR_EX_DATE);
	} while (*year > MAXIMUM_YEAR_EX_DATE || *year < MINIMUM_YEAR_EX_DATE);
	do
	{
		printf("Enter the credit card expiration Month: \n");
		scanf("%d", month);
		if (*month > MONTHS_PER_YEAR || *month < 1)
			printf("Valid credit card month is between %d and %d\n", 1, MONTHS_PER_YEAR);
	} while (*month > MONTHS_PER_YEAR || *month < 1);
}
/*checks if there is a substring in a name*/
customer_t* hasSubString(char subString[], customer_t* customerList, int size, int* newSize)
{
	int i, physicalSize = 1;
	*newSize = 0;
	customer_t* subCustomers = (customer_t*)malloc(sizeof(customer_t) * physicalSize);
	for (i = 0; i < size; i++)
	{
		if (!(strstr(customerList[i].cusName, subString) == NULL))
		{
			if (*newSize == physicalSize)
			{
				physicalSize *= 2;
				subCustomers = (customer_t*)realloc(subCustomers, physicalSize * sizeof(customer_t));
			}
			subCustomers[*newSize] = customerList[i];
			(*newSize)++;
		}
	}
	return subCustomers;
}

void printCustomerList(customer_t* customerList, int logicSize)
{
	int i;
	for (i = 0; i < logicSize; i++)
	{
		printf("[%-1d]: |Customer name: %s| |Credit card number: %s| |expiration date: %d %d|\n", customerList[i].sysLogicNum, customerList[i].cusName, customerList[i].creditCard, (*customerList[i].expirationDate).month, (*customerList[i].expirationDate).year);
	}
}