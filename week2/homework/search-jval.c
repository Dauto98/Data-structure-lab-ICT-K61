#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jval.h"

void swap(Jval* n1, Jval* n2) {
	Jval temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

Jval* createArray(int length) {
	Jval* array = malloc(length * sizeof(Jval));

	for (int i = 0; i < length; i++) {
		array[i] = new_jval_i(i);
	}
	return array;
}

void partition_3_way(Jval* array, long long left, long long right, long long* i, long long* j, int (*compare)(Jval, Jval)) {
	*i = left - 1, *j = right;
	long long p = left - 1, q = right;
	Jval pivot = array[right];

	while (1) {
		while (compare(array[++(*i)], pivot) < 0);

		while (compare(pivot, array[--(*j)]) < 0) {
			if (*j == left) {
				break;
			}
		}

		if (*i >= *j) {
			break;
		}

		swap(&array[*i], &array[*j]);

		if (compare(array[*i], pivot) == 0) {
			p++;
			swap(&array[p], &array[*i]);
		}

		if (compare(array[*j], pivot) == 0) {
			q--;
			swap(&array[q], &array[*j]);
		}
	}

	swap(&array[*i], &array[right]);

	*j = *i - 1;
	for (long long k = left; k < p; k++, (*j)--) {
		swap(&array[k], &array[*j]);
	}

	(*i)++;
	for (long long k = right - 1; k > q; k--, (*i)++) {
		swap(&array[k], &array[*i]);
	}
}

int compareIntJval(Jval j1, Jval j2) {
	return jval_i(j1) - jval_i(j2);
}

int search_gen(Jval* array, long long left, long long right, Jval item, int (*compare)(Jval, Jval)) {
	if (right < left) {
		return -1;
	}
	int i  = (left + right)/2;
	int res = compare(item, array[i]);
	if (res == 0) {
		return i;
	} else if (res < 0) {
		return search_gen(array, left, i-1, item, compare);
	} else {
		return search_gen(array, i+1, right, item, compare);
	}
}

int main(int argc, char const *argv[]) {
	int length = 20;
	Jval* intArray = createArray(length);

	printf("Content of original Array: ");
	for (long long i = 0; i < length; i++) {
		printf("%d; ", jval_i(intArray[i]));
	}
	printf("\n");

	int searchingNumber;
	printf("Enter a number: ");
	scanf("%d", &searchingNumber);

	printf("The index of the number: %d\n", search_gen(intArray, 0, length - 1, new_jval_i(searchingNumber), compareIntJval));

	return 0;
}
