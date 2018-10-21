#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "../../libfdr/jrb.h"
#include "./graph-list-str.h"

Graph createGraph() {
	return make_jrb();
}

void addEdge(Graph graph, char* v1, char* v2) {
	if (isAdjacent(graph, v1, v2) == 1) {
		return;
	}
	JRB vertex = jrb_find_str(graph, v1);
	if (vertex == NULL) {
		// create new tree holding the adjacent list of this vertex
		Graph adjacencyList = createGraph();
		jrb_insert_str(adjacencyList, v2, new_jval_i(1));
		jrb_insert_str(graph, v1, new_jval_v(adjacencyList));
	} else {
		jrb_insert_str(jval_v(vertex->val), v2, new_jval_i(1));
	}

	// add reverse edge
	vertex = jrb_find_str(graph, v2);
	if (vertex == NULL) {
		// create new tree holding the adjacent list of this vertex
		Graph adjacencyList = createGraph();
		jrb_insert_str(adjacencyList, v1, new_jval_i(1));
		jrb_insert_str(graph, v2, new_jval_v(adjacencyList));
	} else {
		jrb_insert_str(jval_v(vertex->val), v1, new_jval_i(1));
	}
}

int getAdjacentVertices(Graph graph, char* v, char** output) {
	JRB vertex = jrb_find_str(graph, v);
	if (vertex == NULL) {
		return 0;
	}
	Graph adjacentList = jval_v(vertex->val);
	JRB adjacentVertex;
	int count = 0;
	jrb_traverse(adjacentVertex, adjacentList) {
		strcpy(output[count], jval_s(adjacentVertex->key));
		count++;
	}
	return count;
}

int isAdjacent(Graph graph, char* v1, char* v2) {
	JRB vertex1 = jrb_find_str(graph, v1);
	if (vertex1 == NULL) {
		return 0;
	}
	JRB vertex2 = jrb_find_str(jval_v(vertex1->val), v2);
	if (vertex2 == NULL) {
		return 0;
	}
	return 1;
}

void dropGraph(Graph graph) {
	JRB vertex;
	jrb_traverse(vertex, graph) {
		jrb_free_tree(jval_v(vertex->val));
	}
	jrb_free_tree(graph);
}
