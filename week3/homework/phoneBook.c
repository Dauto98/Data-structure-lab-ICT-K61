#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phoneBook.h"

PhoneBook* createPhoneBook() {
	PhoneBook* phoneBook = malloc(sizeof(PhoneBook));
	if (phoneBook != NULL) {
		phoneBook->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
		if (phoneBook->entries != NULL) {
			return phoneBook;
		}
	}
	return NULL;
}

void dropPhoneBook(PhoneBook* book) {
	for (int i = 0; i < book->total; i++) {
		free(&(book->entries[i]));
	}
	free(book);
}

void addPhoneNumber(char * name, long number, PhoneBook* book) {
	for (int i = 0; i < book->total; i++) {
		if (strcmp(book->entries[i].name, name) == 0) {
			book->entries[i].number = number;
			return;
		}
	}
	if (book->total >= book->size) {
		PhoneEntry* newBookEntries = realloc(book->entries, sizeof(PhoneEntry) * (book->size + INCREMENTAL_SIZE));
		if (newBookEntries != NULL) {
			book->entries = newBookEntries;
			book->size = book->size + INCREMENTAL_SIZE;
		} else {
			return;
		}
	}
	strcpy(book->entries[book->total].name, name);
	book->entries[book->total].number = number;
	book->total += 1;
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook* book) {
	for (int i = 0; i < book->total; i++) {
		if (strcmp(book->entries[i].name, name) == 0) {
			return &(book->entries[i]);
		}
	}
}
