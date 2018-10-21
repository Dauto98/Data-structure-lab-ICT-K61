#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./graph-list-str.h"

int readData(FILE* fin, Graph stationNameMapping, Graph networkTree) {
	int section = -1;
	char line[100];
	char * a;
	while (fgets(line, 100, fin) != NULL) {
		if (strcmp(line, "[STATIONS]\n") == 0) {
			section = 0;
		} else if (strcmp(line, "[LINES]\n") == 0) {
			section = 1;
		} else if (section == 0) {
			// read station name
			char* key = strtok(line, "=");
			if (key == NULL) {
				printf("Wrong file format\n");
				return 1;
			}
			// use \n to remove the \n at the end of the line
			char* name = strtok(NULL, "\n");
			if (name == NULL) {
				printf("Wrong file format\n");
				return 1;
			}
			jrb_insert_str(stationNameMapping, key, new_jval_s(name));
			JRB test = jrb_find_str(stationNameMapping, "S1");
			if (test == NULL) {
				printf("Not found\n");
			} else {
				printf("%s - %s\n", jval_s(test->key), jval_s(test->val));
			}
		} else if (section == 1) {
			// read network
			// discard the railway name (M1, M2, ....)
			line[strlen(line) - 1] = '\0';
			strtok(line, "=");
			char* prevStation = malloc(sizeof(char) * 100);
			char* nextStation = malloc(sizeof(char) * 100);
			while ((nextStation = strtok(NULL, " ")) != NULL) {
				if (prevStation != NULL) { // not the first station
					printf("%s\n", nextStation);
					JRB test = jrb_find_str(stationNameMapping, nextStation);
					if (test == NULL) {
						printf("Not found\n");
					} else {
						printf("%s - %s\n", jval_s(test->key), jval_s(test->val));
					}
					addEdge(networkTree, prevStation, nextStation);
				}
				strcpy(prevStation, nextStation);
			}
		} else {
			printf("Wrong file format\n");
			return 1;
		}
	}
	// JRB map;
	// jrb_traverse(map, (*stationNameMapping)) {
	// 	printf("%s\n", jval_s(jrb_val(map)));
	// }
	return 0;
}

char* getKeyFromName(char* name, Graph stationNameMapping) {
	JRB mapping;
	jrb_traverse(mapping, stationNameMapping) {
		if (strcmp(name, jval_s(mapping->val)) == 0) {
			return jval_s(mapping->key);
		}
	}
	return NULL;
}

char* getNameFromKey(char* key, Graph stationNameMapping) {
	return jval_s(jrb_find_str(stationNameMapping, key)->val);
}

void findAdjacentStation(char* name, Graph stationNameMapping, Graph networkTree) {
	char* key = getKeyFromName(name, stationNameMapping);
	printf("%s\n", key);
	if (key == NULL) {
		printf("There is no station with that name\n");
		return;
	}
	char** keyArray = malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++) {
		keyArray[i] = malloc(sizeof(char) * 100);
	}
	int count = getAdjacentVertices(networkTree, name, keyArray);
	if (count == 0) {
		printf("No Adjacent station\n");
		return;
	}

	for (int i = 0; i < count; i++) {
		printf("%s - ", getNameFromKey(keyArray[i], stationNameMapping));
	}
	return;
}

int main(int argc, char const *argv[]) {
	FILE* fin = fopen("input.txt", "r");
	if (fin == NULL) {
		printf("Error while opening the file\n");
		return 1;
	}

	Graph stationNameMapping = createGraph();
	Graph networkTree = createGraph();
	int status = readData(fin, stationNameMapping, networkTree);
	// stop the program if failed to read the file
	if (status == 1) {
		return 1;
	}

	int option;
	while (1) {
		printf("MENU\n");
		printf("1 - Find adjacent stations\n");
		printf("2 - Quit\n");

		printf("Enter a number: ");
		scanf("%d", &option);

		while (option != 1 && option != 2) {
			printf("Invalid number, type again: ");
			scanf("%*c");
			scanf("%d", &option);
		}

		if (option == 1) {
			char name[40];
			printf("Enter a station name: ");
			scanf("%*c");
			scanf("%[^\n]s", name);
			findAdjacentStation(name, stationNameMapping, networkTree);
		} else if (option == 2) {
			printf("Bye\n");
			break;
		}
	}

	return 0;
}
