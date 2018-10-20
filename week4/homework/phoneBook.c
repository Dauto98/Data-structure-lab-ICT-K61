#include "../../libfdr/jrb.h"
#include "phoneBook.h"

PhoneBook createPhoneBook() {
	return make_jrb();
}

void dropPhoneBook(PhoneBook book) {
	jrb_free_tree(book);
}

void addPhoneNumber(char * name, long number, PhoneBook book) {
	jrb_insert_str(book, name, new_jval_l(number));
}

PhoneEntry getPhoneNumber(char * name, PhoneBook book) {
	return jrb_find_str(book, name);
}
