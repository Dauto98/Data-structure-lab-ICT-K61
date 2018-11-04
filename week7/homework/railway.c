#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./graph-list-str.h"

int readData(FILE* fin, Graph stationNameMapping, Graph networkTree) {
	int section = -1;
	char line[100];
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
			// copy to malloc pointer so that the string won't get deleted when go out of scope
			char* copiedKey = malloc(sizeof(char) * strlen(key));
			char* copiedName = malloc(sizeof(char) * strlen(name));
			strcpy(copiedKey, key);
			strcpy(copiedName, name);
			jrb_insert_str(stationNameMapping, copiedKey, new_jval_s(copiedName));
		} else if (section == 1) {
			// read network
			// discard the railway name (M1, M2, ....)
			line[strlen(line) - 1] = '\0';
			strtok(line, "=");
			char* prevStation = NULL;
			char* nextStation = NULL;
			while ((nextStation = strtok(NULL, " ")) != NULL) {
				if (prevStation != NULL) { // not the first station
					// copy to malloc pointer so that the string won't get deleted when go out of scope
					char* copiedPrev = malloc(sizeof(char) * strlen(prevStation));
					char* copiedNext = malloc(sizeof(char) * strlen(nextStation));
					strcpy(copiedPrev, prevStation);
					strcpy(copiedNext, nextStation);
					addEdge(networkTree, copiedPrev, copiedNext);
				}
				prevStation = nextStation;
			}
		} else {
			printf("Wrong file format\n");
			return 1;
		}
	}
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
	if (key == NULL) {
		printf("There is no station with that name\n");
		return;
	}
	char** keyArray = malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++) {
		keyArray[i] = malloc(sizeof(char) * 100);
	}
	int count = getAdjacentVertices(networkTree, key, keyArray);
	if (count == 0) {
		printf("No Adjacent station\n");
		return;
	}

	for (int i = 0; i < count; i++) {
		if (i == count) {
			printf("%s", getNameFromKey(keyArray[i], stationNameMapping));
		} else {
			printf("%s - ", getNameFromKey(keyArray[i], stationNameMapping));
		}
	}
	return;
}

void findShortestPath(char* departureStation, char* destinationStation, Graph stationNameMapping, Graph networkTree) {
	char* departureKey = getKeyFromName(departureStation, stationNameMapping);
	if (departureKey == NULL) {
		printf("There is no departure station with that name\n");
		return;
	}

	char* destinationKey = getKeyFromName(destinationStation, stationNameMapping);
	if (destinationKey == NULL) {
		printf("There is no destination station with that name\n");
		return;
	}

	char** keyArray = malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++) {
		keyArray[i] = malloc(sizeof(char) * 100);
	}
	int length = getShortestPath(networkTree, departureKey, destinationKey, keyArray);
	if (length == 0) {
		printf("No path between 2 station\n");
		return;
	}

	printf("\n");
	for (int i = length - 1; i >= 0; i--) {
		if (i == 0) {
			printf("%s", getNameFromKey(keyArray[i], stationNameMapping));
		} else {
			printf("%s - ", getNameFromKey(keyArray[i], stationNameMapping));
		}
	}
	printf("\n");
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
		printf("\nMENU\n");
		printf("1 - Find adjacent stations\n");
		printf("2 - Get shortest path between 2 stations\n");
		printf("3 - Quit\n");

		printf("Enter a number: ");
		scanf("%d", &option);

		while (option != 1 && option != 2 && option != 3) {
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
			char departureStation[40];
			printf("Enter the departure station: ");
			scanf("%*c");
			scanf("%[^\n]s", departureStation);

			char destinationStation[40];
			printf("Enter the destination station: ");
			scanf("%*c");
			scanf("%[^\n]s", destinationStation);
			findShortestPath(departureStation, destinationStation, stationNameMapping, networkTree);
		} else if (option == 3) {
			printf("Bye\n");
			break;
		}
	}

	return 0;
}
