#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	int id;
	float score;
} Student;

int student_compare(void *a, void *b) {
	Student* sa = (Student*)a;
	Student* sb = (Student*)b;

	if (sa->id == sb->id) {
		return 0;
	}

	return (sa->id > sb->id ? 1 : -1);
}

int main(int argc, char const *argv[]) {
	int n = 100;
	Student a[n];

	qsort(a, n, sizeof(Student), student_compare);

	return 0;
}
