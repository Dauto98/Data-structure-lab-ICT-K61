#ifndef _GRAPH_LIST_H_
#define _GRAPH_LIST_H_

#include "../../libfdr/jrb.h"

typedef JRB Graph;

Graph createGraph();

void addEdge(Graph graph, char* v1, char* v2);

int getAdjacentVertices (Graph graph, char* v, char** output);

int isAdjacent(Graph graph, char* v1, char* v2);

void dropGraph(Graph graph);

#endif
