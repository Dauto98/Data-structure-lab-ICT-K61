#include "../libfdr/jrb.h"
#include "graph-list.h"

Graph createGraph() {
	return make_jrb();
}

void addEdge(Graph graph, int v1, int v2) {
	Graph vertex = (Graph) jrb_find_int(graph, v1);
	if (vertex == NULL) {
		// create new tree holding the adjacent list of this vertex
		Graph adjacencyList = createGraph();
		jrb_insert_int(adjacencyList, v2, new_jval_i(1));
		jrb_insert_int(graph, v1, new_jval_v(adjacencyList));
	} else {
		jrb_insert_int(vertex, v2, new_jval_i(1));
	}
}

int getAdjacentVertices (Graph graph, int v, int* output) {

}

void dropGraph(Graph graph);
