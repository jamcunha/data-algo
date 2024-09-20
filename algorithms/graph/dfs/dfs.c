#include "dfs.h"
#include "../../../data-structures/stack/stack.h"

#include <assert.h>
#include <stdlib.h>

// Example of a DFS implemented recursively
// void dfs(graph_list_t *graph, int start) {
//     assert(graph != NULL);
//     assert(start >= 0);
//     assert(start < graph->num_vertices);
//
//     for (int i = 0; i < graph->num_vertices; ++i) {
//         graph->list[i]->visited = false;
//     }
//
//     graph->list[start]->visited = true;
//
//     printf("Vertex: %d\n", start);
//
//     vertex_t *current = graph->list[start];
//     while (current != NULL) {
//         if (!graph->list[current->id]->visited) {
//             dfs(graph, current->id);
//         }
//
//         current = current->next;
//     }
// }

#ifdef GRAPH_LIST_H

int *graph_dfs(graph_list_t *graph, int start) {
    assert(graph != NULL);
    assert(start >= 0);
    assert(start < graph->num_vertices);

    for (int i = 0; i < graph->num_vertices; ++i) {
        graph->list[i]->visited = false;
    }

    int *dfs_order = (int *)malloc(sizeof(int) * graph->num_vertices);
    int dfs_order_index = 0;

    stack_t *stack = stack_create();
    stack_push(stack, start);

    while (!is_stack_empty(stack)) {
        int current_vertex = stack_top(stack); stack_pop(stack);
        dfs_order[dfs_order_index++] = current_vertex;

        vertex_t *current = graph->list[current_vertex];
        while (current != NULL) {
            if (!graph->list[current->id]->visited) {
                graph->list[current->id]->visited = true;
                stack_push(stack, current->id);
            }

            current = current->next;
        }
    }

    destroy_stack(stack);
    return dfs_order;
}

#elif defined(GRAPH_MATRIX_H)

int *graph_dfs(graph_matrix_t *graph, int start) {
    assert(graph != NULL);
    assert(start >= 0);
    assert(start < graph->num_vertices);

    bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));

    int *dfs_order = (int *)malloc(sizeof(int) * graph->num_vertices);
    int dfs_order_index = 0;

    stack_t *stack = stack_create();
    stack_push(stack, start);

    while (!is_stack_empty(stack)) {
        int current_vertex = stack_top(stack); stack_pop(stack);

        dfs_order[dfs_order_index++] = current_vertex;

        for (int i = 0; i < graph->num_vertices; ++i) {
            if (graph->matrix[current_vertex][i] && !visited[i]) {
                visited[i] = true;
                stack_push(stack, i);
            }
        }
    }

    free(visited);
    stack_destroy(stack);
    return dfs_order;
}

#endif
