#include <stdio.h>
#include "phoneBook.h"

int main(int argc, char const *argv[]) {
	int result = initPhonebook();
	if (result != 0) {
		return 1;
	}

	PhoneBook book = createPhoneBook("test.txt");

	result = addPhoneNumber("Nguyen A", 123456789, book);
	if (result != 0) {
		printf("Error while inserting\n");
		return 1;
	}

	result = addPhoneNumber("Nguyen B", 312312321, book);
	if (result != 0) {
		printf("Error while inserting\n");
		return 1;
	}

	result = addPhoneNumber("Nguyen C", 342352543, book);
	if (result != 0) {
		printf("Error while inserting\n");
		return 1;
	}

	result = addPhoneNumber("Nguyen D", 676235776, book);
	if (result != 0) {
		printf("Error while inserting\n");
		return 1;
	}

	int phone = (int) getPhoneNumber("Nguyen B", book);
	printf("%d\n", phone);

	result = closePhoneBook(book);
	if (result != 0) {
		printf("Error while closing file\n");
	}
	return 0;
}
