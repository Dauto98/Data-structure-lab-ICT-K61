#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

void swap(int* n1, int* n2) {
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

int getRandom(int low, int high) {
	return rand() % (high - low + 1) + low;
}

int* createRandomArray(int length) {
	srand(time(0));

	int* array = (int*)malloc(length * sizeof(int));

	for (long long i = 0; i < length; i++) {
		array[i] = getRandom(1, 10);
	}

	return array;
}

int* deepCopyArray(int* array, int length) {
	int* dupArray = (int*)malloc(length * sizeof(int));
	return (int*) memcpy(dupArray, array, length * sizeof(int));
}

int partition_2_way(int* array, long long left, long long right) {
	int pivot = array[right];
	long long i = left - 1;

	for (long long j = left; j < right; j++) {
		if (array[j] <= pivot) {
			i++;
			swap(&array[j], &array[i]);
		}
	}

	swap(&array[i + 1], &array[right]);
	return i + 1;
}

void sort2WayPartition(int* array, long long left, long long right) {
	if (left < right) {
		long long partitionIndex = partition_2_way(array, left, right);

		sort2WayPartition(array, left, partitionIndex - 1);
		sort2WayPartition(array, partitionIndex + 1, right);
	}
}

void partition_3_way(int* array, long long left, long long right, long long* i, long long* j) {
	*i = left - 1, *j = right;
	long long p = left - 1, q = right;
	int pivot = array[right];

	while (1) {
		while (array[++(*i)] < pivot);

		while (pivot < array[--(*j)]) {
			if (*j == left) {
				break;
			}
		}

		if (*i >= *j) {
			break;
		}

		swap(&array[*i], &array[*j]);

		if (array[*i] == pivot) {
			p++;
			swap(&array[p], &array[*i]);
		}

		if (array[*j] == pivot) {
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

void sort3WayPartition(int* array, long long left, long long right) {
	if (left < right) {
		long long i, j;

		partition_3_way(array, left, right, &i, &j);

		sort3WayPartition(array, left, j);
		sort3WayPartition(array, i, right);
	}
}

int* createArray(int length) {
	int* array = malloc(length * sizeof(int));

	for (int i = 0; i < length; i++) {
		array[i] = i;
	}
	return array;
}

int compareInt(const void* n1, const void* n2) {
	int number1 = *((int*)n1);
	int number2 = *((int*)n2);

	return number1 - number2;
}

int search(void* buf, int size, int l, int r, void* item, int (*compare)(const void*, const void*)) {
	if (r < l) {
		return -1;
	}
	int i  = (l + r)/2;
	int res = compare(item, (char*)buf + (size*i));
	if (res == 0) {
		return i;
	} else if (res < 0) {
		return search(buf, size, l, i-1, item, compare);
	} else {
		return search(buf, size, i+1, r, item, compare);
	}
}

int main(int argc, char const *argv[]) {
	int length = 20;
	int* intArray = createArray(length);

	printf("Content of original Array: ");
	for (long long i = 0; i < length; i++) {
		printf("%d; ", intArray[i]);
	}
	printf("\n");

	int searchingNumber;
	printf("Enter a number: ");
	scanf("%d", &searchingNumber);

	printf("The index of the number: %d\n", search(intArray, sizeof(int), 0, length - 1, &searchingNumber, compareInt));

	return 0;
}
