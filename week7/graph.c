#include <stdlib.h>
#include "../libfdr/dllist.h"
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

void BFS(Graph graph, int start, int stop, void (*func)(int)) {
	JRB visited;
	Dllist node, queue;
	int n, output[100], i, u, v;

	queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	visited = make_jrb();

	while (!dll_empty(queue)) {
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);

		if (jrb_find_int(visited, u) == NULL) {
			func(u);
			jrb_insert_int(visited, u, new_jval_i(1));

			if (u == stop) {
				break;
			}

			n = getAdjacentVertices(graph, u, output);
			for (i = 0; i < n; i++) {
				v = output[i];
				if (jrb_find_int(visited, v) == NULL) {
					dll_append(queue, new_jval_i(v));
				}
			}
		}
	}
	jrb_free_tree(visited);
}

void DFS(Graph graph, int start, int stop, void (*func)(int)) {
	JRB visited;
	Dllist node, stack;
	int n, output[100], i, u, v;

	stack = new_dllist();
	dll_prepend(stack, new_jval_i(start));
	visited = make_jrb();

	while (!dll_empty(stack)) {
		node = dll_first(stack);
		u = jval_i(node->val);
		dll_delete_node(node);

		if (jrb_find_int(visited, u) == NULL) {
			func(u);
			jrb_insert_int(visited, u, new_jval_i(1));

			if (u == stop) {
				break;
			}

			n = getAdjacentVertices(graph, u, output);
			for (i = 0; i < n; i++) {
				v = output[i];
				if (jrb_find_int(visited, v) == NULL) {
					dll_prepend(stack, new_jval_i(v));
				}
			}
		}
	}
	jrb_free_tree(visited);
}
