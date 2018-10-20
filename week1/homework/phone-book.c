/**
 * Input file format: 3 part separated by semicolon
 * <name>;<phone number>;<email>
 * e.g.: Nguyen Van I;0905135326;i@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30
#define PHONE_LENGTH 12
#define EMAIL_LENGTH 20
#define LINE_LENGTH 62

typedef struct {
	char name[NAME_LENGTH];
	char phoneNumber[PHONE_LENGTH];
	char email[EMAIL_LENGTH];
} Address;

/**
 * copy all properties from src to dest
 * @param dest
 * @param src
 */
void deepCopyAddress(Address* dest, Address* src) {
	strcpy(dest->name, src->name);
	strcpy(dest->phoneNumber, src->phoneNumber);
	strcpy(dest->email, src->email);
}

/**
 * convert the line read in input file into struct data
 * @param  string one line in the input file
 * @return        a pointer to the new struct, or NULL if an error occur
 */
Address* convertStringtoStruct(char string[]) {
	Address* p = (Address *)malloc(sizeof(Address));
	if (p == NULL) {
		printf("Memory too low\n");
		return NULL;
	}

	// split string by semi colon and store into struct
	strcpy(p->name, strtok(string, ";"));
	strcpy(p->phoneNumber, strtok(NULL, ";"));
	strcpy(p->email, strtok(NULL, ";"));

	// if the data is missing, i.e. string is only separated into 2 part by 1 semi colon,
	// then we return NULL to indicate this line of file is wrong
	if (p->email == NULL) {
		return NULL;
	}
	return p;
}

/**
 * push new Address item to the array, auto expand the array if limit is reached
 * @param pointerToArray pointer point to the (pointer point to the start of the array)
 * @param length         length pointer
 * @param allocatedSize  max length posible of the array (pointer)
 * @param address        new address to push to the array
 */
void pushToArray(Address** pointerToArray, int* length, int* allocatedSize, Address* address) {
	if (*length >= *allocatedSize) {
		printf("Realloc\n");
		*allocatedSize = (*allocatedSize) * 2;
		// printf("%d\n", *allocatedSize);
		Address* temp_array = (Address*)realloc(*pointerToArray, sizeof(Address) * (*allocatedSize));
		if (temp_array == NULL) {
			printf("Realloc failed\n");
			return;
		} else {
			printf("Realloc succeed\n");
			*pointerToArray = temp_array;
		}
	}
	printf("%d\n", *length);
	deepCopyAddress(&((*pointerToArray)[*length]), address);
	(*length)++;
}

void printAddressArray(Address* array, int length) {
	printf("_________________\n");
	for (int i = 0; i < length; i++) {
		// printf("%d) Name: %s\n", i, array[i].name);
		printf("%d) Name: %s; Phone: %s, Email: %s\n", i, array[i].name, array[i].phoneNumber, array[i].email);
	}
	printf("_________________\n");
}

int compareAddressByName(const void* add1, const void* add2) {
	Address* address1 = (Address*) add1;
	Address* address2 = (Address*) add2;

	return strcmp(address1->name, address2->name);
}

int main(int argc, char const *argv[]) {
	int allocatedSize = 8;
	int length = 0;
	Address* addressArray = (Address*)malloc(sizeof(Address) * allocatedSize);

	FILE *fin = fopen("input.txt", "r");
	char line[LINE_LENGTH];

	if (fin == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	// Read from file and contruct a stack
	char* result = NULL;
	while ((result = fgets(line, LINE_LENGTH, fin)) != NULL) {
		Address *temp = convertStringtoStruct(line);
		// printf("%s\n", result);
		printf("current file pointer position: %ld\n", ftell(fin));
		// if the data has errors, the program ignore it
		if (temp != NULL) {
			pushToArray(&addressArray, &length, &allocatedSize, temp);
			printf("current file pointer position: %ld\n", ftell(fin));
		}
		printf("____\n");
	}
	printf("%p\n", result);
	printf("%ld\n", ftell(fin));

	printAddressArray(addressArray, length);

	qsort(addressArray, length, sizeof(Address), compareAddressByName);

	printAddressArray(addressArray, length);

	return 0;
}
