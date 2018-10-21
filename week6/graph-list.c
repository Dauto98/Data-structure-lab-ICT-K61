#include <stddef.h>
#include "../libfdr/jrb.h"
#include "graph-list.h"

Graph createGraph() {
	return make_jrb();
}

void addEdge(Graph graph, int v1, int v2) {
	JRB vertex = jrb_find_int(graph, v1);
	if (vertex == NULL) {
		// create new tree holding the adjacent list of this vertex
		Graph adjacencyList = createGraph();
		jrb_insert_int(adjacencyList, v2, new_jval_i(1));
		jrb_insert_int(graph, v1, new_jval_v(adjacencyList));
	} else {
		jrb_insert_int(jval_v(vertex->val), v2, new_jval_i(1));
	}

	// add reverse edge
	JRB vertex = jrb_find_int(graph, v2);
	if (vertex == NULL) {
		// create new tree holding the adjacent list of this vertex
		Graph adjacencyList = createGraph();
		jrb_insert_int(adjacencyList, v1, new_jval_i(1));
		jrb_insert_int(graph, v2, new_jval_v(adjacencyList));
	} else {
		jrb_insert_int(jval_v(vertex->val), v1, new_jval_i(1));
	}
}

int getAdjacentVertices(Graph graph, int v, int* output) {
	JRB vertex = jrb_find_int(graph, v);
	if (vertex == NULL) {
		return 0;
	}
	Graph adjacentList = jval_v(vertex->val);
	JRB adjacentVertex;
	int count = 0;
	jrb_traverse(adjacentVertex, adjacentList) {
		output[count++] = jval_i(adjacentVertex->key);
	}
	return count;
}

void dropGraph(Graph graph) {
	JRB vertex;
	jrb_traverse(vertex, graph) {
		jrb_free_tree(jval_v(vertex->val));
	}
	jrb_free_tree(graph);
}
