#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdbool.h>

typedef struct {
    bool **matrix;
    int num_vertices;
    int capacity;
} graph_matrix_t;

// To check if there is an edge between two vertices,
// we can check graph->matrix[vertex1][vertex2]

// if num_vertices = 0 then the initial capacity is 10
graph_matrix_t *graph_matrix_create(int num_vertices);

void graph_matrix_add_vertex(graph_matrix_t *graph);

void graph_matrix_remove_vertex(graph_matrix_t *graph, int v);

void graph_matrix_add_edge(graph_matrix_t *graph, int v1, int v2);

void graph_matrix_remove_edge(graph_matrix_t *graph, int v1, int v2);

void graph_matrix_add_directed_edge(graph_matrix_t *graph, int v1, int v2);

void graph_matrix_remove_directed_edge(graph_matrix_t *graph, int v1, int v2);

void graph_matrix_destroy(graph_matrix_t *graph);

#endif // GRAPH_MATRIX_H
