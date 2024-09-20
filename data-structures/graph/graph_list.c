#include "graph_list.h"

#include <assert.h>
#include <stdlib.h>

static const int INITIAL_CAPACITY = 10;

static vertex_t *vertex_create(int id) {
    vertex_t *vertex = (vertex_t *)malloc(sizeof(vertex_t));
    vertex->id = id;
    vertex->next = NULL;

    return vertex;
}

graph_list_t *graph_list_create(int num_vertices) {
    graph_list_t *graph = (graph_list_t *)malloc(sizeof(graph_list_t));
    graph->num_vertices = 0;
    graph->capacity = num_vertices == 0 ? INITIAL_CAPACITY : num_vertices;
    graph->list = (vertex_t **)calloc(graph->capacity, sizeof(vertex_t *));

    return graph;
}

void graph_list_add_vertex(graph_list_t *graph) {
    assert(graph != NULL);

    if (graph->num_vertices == graph->capacity) {
        graph->capacity *= 2;
        graph->list = (vertex_t **)realloc(graph->list, graph->capacity * sizeof(vertex_t *));

        for (int i = graph->num_vertices; i < graph->capacity; ++i) {
            graph->list[i] = NULL;
        }
    }

    graph->num_vertices++;
}

void graph_list_remove_vertex(graph_list_t *graph, int v) {
    assert(graph != NULL);
    assert(v >= 0 && v < graph->num_vertices);

    vertex_t *current = graph->list[v];
    while (current != NULL) {
        vertex_t *temp = current;
        current = current->next;
        free(temp);
    }

    for (int i = 0; i < graph->num_vertices; ++i) {
        if (i == v) {
            continue;
        }

        current = graph->list[i];
        vertex_t *prev = NULL;
        while (current != NULL && current->id != v) {
            prev = current;
            current = current->next;
        }

        if (current != NULL) {
            if (prev == NULL) {
                graph->list[i] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
        }
    }

    for (int i = v; i < graph->num_vertices - 1; ++i) {
        graph->list[i] = graph->list[i + 1];
    }

    graph->list[graph->num_vertices - 1] = NULL;
    graph->num_vertices--;
}

void graph_list_add_edge(graph_list_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0 && v1 < graph->num_vertices);
    assert(v2 >= 0 && v2 < graph->num_vertices);

    vertex_t *new_edge = vertex_create(v2);
    new_edge->next = graph->list[v1];
    graph->list[v1] = new_edge;

    new_edge = vertex_create(v1);
    new_edge->next = graph->list[v2];
    graph->list[v2] = new_edge;
}

void graph_list_remove_edge(graph_list_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0 && v1 < graph->num_vertices);
    assert(v2 >= 0 && v2 < graph->num_vertices);

    vertex_t *current = graph->list[v1];
    vertex_t *prev = NULL;
    while (current != NULL && current->id != v2) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            graph->list[v1] = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }

    current = graph->list[v2];
    prev = NULL;
    while (current != NULL && current->id != v1) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            graph->list[v2] = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }
}

void graph_list_add_directed_edge(graph_list_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0 && v1 < graph->num_vertices);
    assert(v2 >= 0 && v2 < graph->num_vertices);

    vertex_t *new_edge = malloc(sizeof(vertex_t));
    new_edge->id = v2;
    new_edge->next = graph->list[v1];
    graph->list[v1] = new_edge;
}

void graph_list_remove_directed_edge(graph_list_t *graph, int v1, int v2) {
    assert(graph != NULL);
    assert(v1 >= 0 && v1 < graph->num_vertices);
    assert(v2 >= 0 && v2 < graph->num_vertices);

    vertex_t *current = graph->list[v1];
    vertex_t *prev = NULL;
    while (current != NULL && current->id != v2) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            graph->list[v1] = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }
}

void graph_list_destroy(graph_list_t *graph) {
    assert(graph != NULL);

    for (int i = 0; i < graph->num_vertices; ++i) {
        vertex_t *current = graph->list[i];
        while (current != NULL) {
            vertex_t *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->list);
    free(graph);
}
