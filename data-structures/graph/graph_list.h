#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

typedef struct vertex {
    int id;
    struct vertex *next;

    // optional fields for algorithms
} vertex_t;

typedef struct {
    vertex_t **list;
    int num_vertices;
    int capacity;
} graph_list_t;

// if num_vertices = 0 then the initial capacity is 10
graph_list_t *graph_list_create(int num_vertices);

void graph_list_add_vertex(graph_list_t *graph);

void graph_list_remove_vertex(graph_list_t *graph, int v);

void graph_list_add_edge(graph_list_t *graph, int v1, int v2);

void graph_list_remove_edge(graph_list_t *graph, int v1, int v2);

void graph_list_add_directed_edge(graph_list_t *graph, int v1, int v2);

void graph_list_remove_directed_edge(graph_list_t *graph, int v1, int v2);

void graph_list_destroy(graph_list_t *graph);

#endif // GRAPH_LIST_H
