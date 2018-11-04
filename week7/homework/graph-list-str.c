#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../libfdr/jrb.h"
#include "../../libfdr/dllist.h"
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

int getShortestPath(Graph graph, char* start, char* end, char** output) {
	// visited: key: node, value: 1 (dummy value)
	// predecessor: key: descendant node, value: predecessor node
	JRB visited, predecessor;
	visited = make_jrb();
	predecessor = make_jrb();

	// create queue to hold "to be visited" node
	Dllist queue = new_dllist();
	dll_append(queue, new_jval_s(start));

	int found = 0;
	while (!dll_empty(queue)) {
		// get 1st node in the queue
		Dllist node = dll_first(queue);
		char* key = jval_s(node->val);
		dll_delete_node(node);

		// we do nothing if the key has been visited
		if (jrb_find_str(visited, key) == NULL) {
			// mark node as visited
			jrb_insert_str(visited, key, new_jval_i(1));
			if (strcmp(key, end) == 0) {
				found = 1;
				break;
			}

			char** keyArray = malloc(sizeof(char*) * 100);
			for (int i = 0; i < 100; i++) {
				keyArray[i] = malloc(sizeof(char) * 100);
			}
			int length = getAdjacentVertices(graph, key, keyArray);
			for (int i = 0; i < length; i++) {
				char* adjKey = keyArray[i];
				// if the next key hasn't been visited
				if (jrb_find_str(visited, adjKey) == NULL) {
					// mark the next key that next key can be arrive from this key
					jrb_insert_str(predecessor, adjKey, new_jval_s(key));
					// add the next key to the queue
					dll_append(queue, new_jval_s(adjKey));
				}
			}
		}
	}

	if (found == 0) {
		return 0;
	}
	int count = 0;
	char* crawl = end;
	strcpy(output[count], crawl);
	count++;
	while (jrb_find_str(predecessor, crawl) != NULL) {
		crawl = jval_s(jrb_find_str(predecessor, crawl)->val);
		strcpy(output[count], crawl);
		count++;
	}
	jrb_free_tree(visited);
	jrb_free_tree(predecessor);
	free_dllist(queue);
	return count;
}


void dropGraph(Graph graph) {
	JRB vertex;
	jrb_traverse(vertex, graph) {
		jrb_free_tree(jval_v(vertex->val));
	}
	jrb_free_tree(graph);
}
