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

int compareInt(const void* n1, const void* n2) {
	int number1 = *((int*)n1);
	int number2 = *((int*)n2);

	return number1 - number2;
}

int main(int argc, char const *argv[]) {
	// create random arrays with length
	int length = 100000;
	int* intArray = createRandomArray(length);
	int* dupIntArray1 = deepCopyArray(intArray, length);
	int* dupIntArray2 = deepCopyArray(intArray, length);
	int* dupIntArray3 = deepCopyArray(intArray, length);

	// printf("Content of original Array: ");
	// for (long long i = 0; i < length; i++) {
	// 	printf("%d; ", intArray[i]);
	// }
	// printf("\n");

	struct timeval sort2WayStart, sort2WayEnd, sort3WayStart, sort3WayEnd, qsortStart, qsortEnd;
  double sort2WayTime, sort3WayTime, qsortTime;

	gettimeofday(&sort2WayStart, NULL);
	sort2WayPartition(dupIntArray1, 0, length - 1);
	gettimeofday(&sort2WayEnd, NULL);

	gettimeofday(&sort3WayStart, NULL);
	sort3WayPartition(dupIntArray2, 0, length - 1);
	gettimeofday(&sort3WayEnd, NULL);

	gettimeofday(&qsortStart, NULL);
	qsort(dupIntArray3, length, sizeof(int), compareInt);
	gettimeofday(&qsortEnd, NULL);

	// printf("Content of sorted array using 2 way: ");
	// for (int i = 0; i < length; i++) {
	// 	printf("%d; ", dupIntArray1[i]);
	// }
	// printf("\n");
  //
	// printf("Content of sorted array using 3 way: ");
	// for (long long i = 0; i < length; i++) {
	// 	printf("%d; ", dupIntArray2[i]);
	// }
	// printf("\n");

	sort2WayTime = (sort2WayEnd.tv_sec - sort2WayStart.tv_sec)*1000000 + (sort2WayEnd.tv_usec - sort2WayStart.tv_usec);
	sort3WayTime = (sort3WayEnd.tv_sec - sort3WayStart.tv_sec)*1000000 + (sort3WayEnd.tv_usec - sort3WayStart.tv_usec);
	qsortTime = (qsortEnd.tv_sec - qsortStart.tv_sec)*1000000 + (qsortEnd.tv_usec - qsortStart.tv_usec);
	printf("Time to run 2 way: %f\n", sort2WayTime/1000000);
	printf("Time to run 3 way: %f\n", sort3WayTime/1000000);
	printf("Time to run qsort: %f\n", qsortTime/1000000);

	return 0;
}
