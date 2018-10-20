#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bt-5.0.0/inc/btree.h"
#include "phoneBook.h"

int initPhonebook() {
	return btinit();
}

PhoneBook createPhoneBook(char* fileName) {
	FILE* fin = fopen(fileName, "r");
	if (fin == NULL) {
		// fclose(fin);
		return btcrt(fileName, 0, FALSE);
	} else {
		// fclose(fin);
		return btopn(fileName, 0, FALSE);
	}
}

void dropPhoneBook(PhoneBook book) {
	int result;
	btpos(book, ZSTART);
	result = bdelky(book, NULL);
	if (result == QNOKEY) {
		closePhoneBook(book);
		return;
	}
	char* key;
	BTint value;
	result = bnxtky(book, key, &value);
	while (result != QNOKEY) {
		bdelky(book, key);
		result = bnxtky(book, key, &value);
	}
	closePhoneBook(book);
	return;
}

int closePhoneBook(PhoneBook book) {
	return btcls(book);
}

int addPhoneNumber(char * name, long number, PhoneBook book) {
	BTint phoneNumber = number;
	return binsky(book, name, phoneNumber);
}

BTint getPhoneNumber(char * name, PhoneBook book) {
	BTint phoneNumber;
	int result = bfndky(book, name, &phoneNumber);
	btpos(book, ZSTART);
	if (result == 0) {
		return phoneNumber;
	} else {
		return -1;
	}
}
