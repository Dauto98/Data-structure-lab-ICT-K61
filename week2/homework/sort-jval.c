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

Jval getRandom(int low, int high) {
	return new_jval_i(rand() % (high - low + 1) + low);
}

Jval* createRandomArray(int length) {
	srand(time(0));

	Jval* array = (Jval*)malloc(length * sizeof(Jval));

	for (long long i = 0; i < length; i++) {
		array[i] = getRandom(1, 10);
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

void sort_gen(Jval* array, long long left, long long right, int (*compare)(Jval, Jval)) {
	if (left < right) {
		long long i, j;

		partition_3_way(array, left, right, &i, &j, compare);

		sort_gen(array, left, j, compare);
		sort_gen(array, i, right, compare);
	}
}

int compareIntJval(Jval j1, Jval j2) {
	return jval_i(j1) - jval_i(j2);
}

int main(int argc, char const *argv[]) {
	int length = 100;
	Jval* intArray = createRandomArray(length);

	printf("Content of original Array: ");
	for (long long i = 0; i < length; i++) {
		printf("%d; ", jval_i(intArray[i]));
	}
	printf("\n");

	sort_gen(intArray, 0, length - 1, compareIntJval);

	printf("\n");
	printf("Content of sorted Array: ");
	for (long long i = 0; i < length; i++) {
		printf("%d; ", jval_i(intArray[i]));
	}
	printf("\n");

	return 0;
}
