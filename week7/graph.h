#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct {
	int* matrix;
	int sizemax;
} Graph;

Graph createGraph(int sizemax);

void addEdge(Graph graph, int v1, int v2);

int adjacent(Graph graph, int v1, int v2);

int getAdjacentVertices(Graph graph, int vertex, int* output);

void dropGraph(Graph graph);

void BFS(Graph graph, int start, int stop, void (*func)(int));

void DFS(Graph graph, int start, int stop, void (*func)(int));

#endif
