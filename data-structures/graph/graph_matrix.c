#include "graph_matrix.h"

#include <assert.h>
#include <stdlib.h>

static const int INITIAL_CAPACITY = 10;

graph_matrix_t *graph_matrix_create(int num_vertices) {
    graph_matrix_t *graph = malloc(sizeof(graph_matrix_t));
    graph->num_vertices = 0;
    graph->capacity = num_vertices == 0 ? INITIAL_CAPACITY : num_vertices;

    graph->matrix = malloc(graph->capacity * sizeof(bool *));
    for (int i = 0; i < graph->capacity; i++) {
        graph->matrix[i] = calloc(graph->capacity, sizeof(bool));
    }

    return graph;
}

void graph_matrix_add_vertex(graph_matrix_t *graph) {
    assert(graph != NULL);

    // If the number of vertices is equal to the capacity, double the capacity
    if (graph->num_vertices == graph->capacity) {
        graph->capacity *= 2;
        graph->matrix = realloc(graph->matrix, graph->capacity * sizeof(bool *));

        for (int i = 0; i < graph->num_vertices; ++i) {
            graph->matrix[i] = realloc(graph->matrix[i], graph->capacity * sizeof(bool));
            graph->matrix[graph->num_vertices + i] = calloc(graph->capacity, sizeof(bool));
        }
    }

    graph->num_vertices++;
}

void graph_matrix_remove_vertex(graph_matrix_t *graph, int v) {
    assert(graph != NULL);
    assert(v >= 0);
    assert(v < graph->num_vertices);

    for (int i = v; i < graph->num_vertices - 1; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            graph->matrix[i][j] = graph->matrix[i + 1][j];
        }
    }

    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = v; j < graph->num_vertices - 1; j++) {
            graph->matrix[i][j] = graph->matrix[i][j + 1];
        }
    }

    graph->num_vertices--;
}

void graph_matrix_add_edge(graph_matrix_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0);
    assert(v2 >= 0);
    assert(v1 < graph->num_vertices);
    assert(v2 < graph->num_vertices);

    graph->matrix[v1][v2] = true;
    graph->matrix[v2][v1] = true;
}

void graph_matrix_remove_edge(graph_matrix_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0);
    assert(v2 >= 0);
    assert(v1 < graph->num_vertices);
    assert(v2 < graph->num_vertices);

    graph->matrix[v1][v2] = false;
    graph->matrix[v2][v1] = false;
}

void graph_matrix_add_directed_edge(graph_matrix_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0);
    assert(v2 >= 0);
    assert(v1 < graph->num_vertices);
    assert(v2 < graph->num_vertices);

    graph->matrix[v1][v2] = true;
}

void graph_matrix_remove_directed_edge(graph_matrix_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0);
    assert(v2 >= 0);
    assert(v1 < graph->num_vertices);
    assert(v2 < graph->num_vertices);

    graph->matrix[v1][v2] = false;
}

void graph_matrix_destroy(graph_matrix_t *graph) {
    assert (graph != NULL);

    for (int i = 0; i < graph->capacity; i++) {
        free(graph->matrix[i]);
    }

    free(graph->matrix);
    free(graph);
}
