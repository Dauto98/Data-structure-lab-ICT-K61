#ifndef __DIRECTED_GRAPH_ALIST__
#define __DIRECTED_GRAPH_ALIST__

#include "../libfdr/dllist.h"
#include "../libfdr/jrb.h"

// We have the list of vertices is a rbt, and each node will point to a small rbt
typedef JRB Graph;

Graph CreateGraph();
void DropGraph(Graph graph);
void AddEdge(Graph graph, char* v1, char* v2);
int IsAdjacent(Graph graph, char* v1, char* v2);
int GetAdjacentVertices(Graph graph, char* vertex, char** output)

// *output are a list of adjacent vertex
int GetInDegree(Graph graph, int vertex, int *output);
int GetOutDegree(Graph graph, int vertex, int *output);

int IsDAG(Graph graph);
JRB GetTopologicalSortedList(Graph graph);

// These BFS, DFS, ShortestPath(using BFS) is only used when graph is fully connected and has no cycle
void BFS(Graph graph, int start, int end, void(*PrintVertex)(int)); // If traverse all vertices, set end = -1
void DFS(Graph graph, int start, int end, void(*PrintVertex)(int));
Dllist ShortestPath(Graph graph, int start, int stop);
#endif
