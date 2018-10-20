#include "stdlib.h"
#include "graph.h"

Graph createGraph(int sizemax) {
	Graph graph;
	graph.sizemax = sizemax;
	graph.matrix = malloc(sizeof(int) * sizemax * sizemax);
	if (graph.matrix != NULL) {
		for (int i = 0; i < sizemax*sizemax; i++) {
			graph.matrix[i] = 0;
		}
	}
	return graph;
}

void addEdge(Graph graph, int v1, int v2) {
	graph.matrix[v1 + v2*graph.sizemax] = 1;
	graph.matrix[v2 + v1*graph.sizemax] = 1;
}

int adjacent(Graph graph, int v1, int v2) {
	return graph.matrix[v1 + v2*graph.sizemax];
}

int getAdjacentVertices(Graph graph, int vertex, int* output) {
	int total = 0;
	for (int i = 0; i < graph.sizemax; i++) {
		if (adjacent(graph, vertex, i*graph.sizemax)) {
			output[total] = i;
			total++;
		}
	}
	return total;
}

void dropGraph(Graph graph) {
	free(graph.matrix);
	graph.matrix = NULL;
	graph.sizemax = 0;
}
