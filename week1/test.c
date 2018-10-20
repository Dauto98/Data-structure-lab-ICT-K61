#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

	for (int i = 0; i < length; i++) {
		array[i] = getRandom(1, 10);
	}

	return array;
}

int* deepCopyArray(int* array, int length) {
	int* dupArray = (int*)malloc(length * sizeof(int));
	return (int*) memcpy(dupArray, array, length * sizeof(int));
}

int partition_2_way(int* array, int left, int right) {
	int pivot = array[right];
	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (array[j] <= pivot) {
			i++;
			swap(&array[j], &array[i]);
		}
	}

	swap(&array[i + 1], &array[right]);
	return i + 1;
}

void sort2WayPartition(int* array, int left, int right) {
	if (left < right) {
		int partitionIndex = partition_2_way(array, left, right);

		sort2WayPartition(array, left, partitionIndex - 1);
		sort2WayPartition(array, partitionIndex + 1, right);
	}
}

int main(void) {
  int length = 100;
	int* intArray = createRandomArray(length);
  int* dupIntArray1 = deepCopyArray(intArray, length);

  printf("Content of original Array: ");
	for (int i = 0; i < length; i++) {
		printf("%d; ", intArray[i]);
	}
	printf("\n");

  sort2WayPartition(dupIntArray1, 0, length - 1);

  printf("Content of sorted array u: ");
  for (int i = 0; i < length; i++) {
    printf("%d; ", dupIntArray1[i]);
  }
  printf("\n");

  return 0;
}
