#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
	char name[80];
	long number;
} PhoneEntry;

typedef struct {
	PhoneEntry *entries;
	int total;
	int size;
} PhoneBook;

PhoneBook* createPhoneBook();

void dropPhoneBook(PhoneBook* book);

void addPhoneNumber(char * name, long number, PhoneBook* book);

PhoneEntry * getPhoneNumber(char * name, PhoneBook* book);

#endif
