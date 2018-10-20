#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

#include "../bt-5.0.0/inc/bt.h"

typedef BTA PhoneEntry;
typedef PhoneEntry* PhoneBook;

int initPhonebook();

PhoneBook createPhoneBook(char* fileName);

void dropPhoneBook(PhoneBook book);

int closePhoneBook(PhoneBook book);

int addPhoneNumber(char * name, long number, PhoneBook book);

BTint getPhoneNumber(char * name, PhoneBook book);

#endif
