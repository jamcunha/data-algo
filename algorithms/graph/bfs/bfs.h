#ifndef GRAPH_BFS_H
#define GRAPH_BFS_H

#ifdef GRAPH_LIST_H

#include "../../../data-structures/graph/graph_list.h"
int *graph_bfs(graph_list_t *graph, int start);

#elif defined(GRAPH_MATRIX_H)

#include "../../../data-structures/graph/graph_matrix.h"
int *graph_bfs(graph_matrix_t *graph, int start);

#endif

#endif // GRAPH_BFS_H
