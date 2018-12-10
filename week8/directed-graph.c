#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libfdr/dllist.h"
#include "../libfdr/jrb.h"
#include "graph_alist.h"

//
// Utilites functions
//
int Visited(JRB visited, int vertex) {
    JRB node = jrb_find_int(visited, vertex);
    if (node == NULL) {
        return 0;
    }

    return jval_i(node->val);
}
//
// END OF Utilities functions
//
Graph CreateGraph() {
  return make_jrb();
}

/**
 * Delete all adjacency-list tree and then delete the vertices tree
 */
void DropGraph(Graph graph) {
  JRB node;
  jrb_traverse(node, graph) {
		jrb_free_tree(jval_v(node->val));
	}
  jrb_free_tree(graph);
}

/**
 * If the list is initiated then we will add new connected vertex to that list
 * If not then we will initiate that list before adding
 */
void AddEdge(Graph graph, char* v1, char* v2) {
    JRB alist;

    // Initialize adjacency list for v1 if needed
    JRB node = jrb_find_str(graph, v1);
    if (node != NULL) {
      alist = jval_v(node->val);
    } else {
      alist = make_jrb();
      jrb_insert_str(graph, v1, new_jval_v(alist));
    }
    // If v1 is not connected to v2, connects them
    if (jrb_find_str(alist, v2) == NULL) {
      jrb_insert_str(alist, v2, new_jval_i(1));
    }
}

/**
 * If the tree doesn't have vertex v1 OR v2 is not in the alist of v1, return 0 (false)
 * Else return 1 (true)
 */
int IsAdjacent(Graph graph, char* v1, char* v2) {
  JRB node = jrb_find_str(graph, v1);
  if (node == NULL) {
		return 0;
	}

  JRB alist = jval_v(node->val);
  if (jrb_find_str(alist, v2) == NULL) {
    return 0;
  }
  return 1;
}

int GetAdjacentVertices(Graph graph, char* v, char** output) {
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

/**
 * Traverse all alist which are not belong to vertex
 * If vertex is found in an alist, aka has path from current node to our vertex -> update output
 */
int GetInDegree(Graph graph, char* vertex, char** output) {
  JRB node;
	JRB alist_node;
  char* current_node;
  int count = 0;

  jrb_traverse(node, graph) {
    current_node = jval_s(node->key);
    if (strcmp(current_node, vertex) != 0) {
      JRB alist = jval_v(node->val);
      jrb_traverse(alist_node, alist) {
        if (strcmp(jval_s(alist_node->key), vertex) == 0) {
					strcpy(output[count], current_node);
          count++;
        }
      }
    }
  }
  return count;
}

int GetOutDegree(Graph graph, char* vertex, char** output) {
  JRB node = jrb_find_str(graph, vertex);
  if (node == NULL) {
    return 0;
  }

  JRB alist = jval_v(node->val);
  int count = 0;
  jrb_traverse(node, alist) {
    strcpy(output[count], jval_i(node->key));
		count++;
  }
  return count;
}

/**
 * Run DFS on all node. If we can return to the source -> IsDAG
 */
int IsDAGUtil(JRB vertex, JRB visited, JRB recursionStack) {
	if (jrb_find_str(visited, vertex) == NULL) {
		jrb_insert_str(visited, vertex, new_jval_i(1));
		jrb_insert_str(recursionStack, vertex, new_jval_i(1));

		JRB adjList = jval_v(vertex->val);
		JRB adjNode;
		jrb_traverse(adjNode, adjList) {
			if (jrb_find_str(visited, adjNode) != NULL && IsDAGUtil(adjNode, visited, recursionStack) == 1) {
				return 1;
			} else if (jrb_find_str(recursionStack, vertex) != NULL) {
				return 1;
			}
		}
	}
	jrb_delete_node(jrb_find_str(recursionStack, vertex));
	return 0;
}

int IsDAG(Graph graph) {
	JRB visited = make_jrb();
	JRB recursionStack = make_jrb();
	JRB vertex;

	jrb_traverse(vertex, graph) {
		if (IsDAGUtil(vertex, visited, recursionStack) == 1) {
			return 1;
		}
	}
	return 0;
}

JRB GetTopologicalSortedList(Graph graph) {
    // Using Kahn's Algorithm
    if (!IsDAG(graph)) {
        return NULL;
    }

    JRB list = make_jrb();
    Dllist queue = new_dllist();
}

void BFS(Graph graph, int start, int stop, void(*PrintVertex)(int)) {
    int totalVertices = 0;
    JRB node;

    JRB visited = make_jrb();
    // Initialize as not visited
    jrb_traverse(node, graph) {
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
        totalVertices++;
    }

    Dllist queue = new_dllist();
    Jval current_node;
    // Append the first vertex to the list
    dll_append(queue, new_jval_i(start));

    while (!dll_empty(queue)) {
        current_node = dll_first(queue)->val;
        dll_delete_node(dll_first(queue));

        if (!Visited(visited, jval_i(current_node))) {
            PrintVertex(jval_i(current_node));

            // Stop traverse if met end vertex
            if (jval_i(current_node) == stop) {
                return;
            }

            // Set the current node as visited
            jrb_find_int(visited, jval_i(current_node))->val = new_jval_i(1);

            // Enqueue all connected vertices
            int adj[totalVertices];
            int totalAdj = 0;
            totalAdj = GetAdjacentVertices(graph, jval_i(current_node), adj);
            for (int i = 0; i < totalAdj; i++) {
                if (!Visited(visited, adj[i])) {
                    dll_append(queue, new_jval_i(adj[i]));
                }
            }
        }
    }
}

void DFS(Graph graph, int start, int stop, void(*PrintVertex)(int)) {
    int totalVertices = 0;
    JRB node;

    JRB visited = make_jrb();
    // Initialize as not visited
    jrb_traverse(node, graph) {
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
        totalVertices++;
    }

    Dllist stack = new_dllist();
    Jval current_node;
    // Append the first vertex to the list
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack)) {
        current_node = dll_last(stack)->val;
        dll_delete_node(dll_last(stack));

        if (!Visited(visited, jval_i(current_node))) {
            PrintVertex(jval_i(current_node));

            // Stop traverse if met end vertex
            if (jval_i(current_node) == stop) {
                return;
            }

            // Set the current node as visited
            jrb_find_int(visited, jval_i(current_node))->val = new_jval_i(1);

            // Push all connected vertices to the stack
            int adj[totalVertices];
            int totalAdj = 0;
            totalAdj = GetAdjacentVertices(graph, jval_i(current_node), adj);
            for (int i = 0; i < totalAdj; i++) {
                if (!Visited(visited, adj[i])) {
                    dll_append(stack, new_jval_i(adj[i]));
                }
            }
        }
    }
}

Dllist ShortestPath(Graph graph, int start, int stop) {
    int totalVertices = 0;
    JRB node;

    JRB visited = make_jrb();
    JRB previous_node = make_jrb();

    // Initialize as not visited and no previous node
    jrb_traverse(node, graph) {
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
        //jrb_insert_int(previous_node, jval_i(node->key), new_jval_i(-1));
        totalVertices++;
    }

    Dllist queue = new_dllist();
    Jval current_node;
    // Append the first vertex to the list & set previous node of starting node as -1
    dll_append(queue, new_jval_i(start));
    jrb_insert_int(previous_node, start, new_jval_i(-1));

    while (!dll_empty(queue)) {
        current_node = dll_first(queue)->val;
        dll_delete_node(dll_first(queue));

        if (!Visited(visited, jval_i(current_node))) {
            // Stop traverse and output shortest path if met end vertex
            if (jval_i(current_node) == stop) {
                Dllist shortest_path = new_dllist();
                dll_prepend(shortest_path, current_node);

                // Traceback
                while (jval_i(current_node) != start) {
                    current_node = jrb_find_int(previous_node, jval_i(current_node))->val;
                    dll_prepend(shortest_path, current_node);
                }
                return shortest_path;
            }

            // Set the current node as visited
            jrb_find_int(visited, jval_i(current_node))->val = new_jval_i(1);

            // Enqueue all connected vertices & set previous_node of those as this node
            int adj[totalVertices];
            int totalAdj = 0;
            totalAdj = GetAdjacentVertices(graph, jval_i(current_node), adj);
            for (int i = 0; i < totalAdj; i++) {
                if (!Visited(visited, adj[i])) {
                    dll_append(queue, new_jval_i(adj[i]));
                    jrb_insert_int(previous_node, adj[i], current_node);
                }
            }
        }
    }
}
