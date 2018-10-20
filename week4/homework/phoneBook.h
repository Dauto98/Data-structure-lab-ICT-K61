#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

typedef JRB PhoneEntry;
typedef PhoneEntry PhoneBook;

PhoneBook createPhoneBook();

void dropPhoneBook(PhoneBook book);

void addPhoneNumber(char * name, long number, PhoneBook book);

PhoneEntry getPhoneNumber(char * name, PhoneBook book);

#endif
