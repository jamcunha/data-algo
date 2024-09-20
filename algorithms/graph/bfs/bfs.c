#include "bfs.h"
#include "../../../data-structures/queue/queue.h"

#include <assert.h>
#include <stdlib.h>

#ifdef GRAPH_LIST_H

int *graph_bfs(graph_list_t *graph, int start) {
    assert(graph != NULL);
    assert(start >= 0);
    assert(start < graph->num_vertices);

    // Array to store the order of vertices visited in BFS
    int *bfs_order = (int *)malloc(sizeof(int) * graph->num_vertices);
    int bfs_order_index = 0;

    // Reset the visited flag for all vertices
    for (int i = 0; i < graph->num_vertices; ++i) {
        graph->list[i]->visited = false;
    }

    queue_t *queue = queue_create();

    // Mark the start vertex as visited and enqueue it
    graph->list[start]->visited = true;
    queue_enqueue(queue, start);

    while (!queue_is_empty(queue)) {
        // Dequeue a vertex from the queue
        int current_vertex = queue_dequeue(queue);

        // Add the dequeued vertex to the BFS order
        bfs_order[bfs_order_index++] = current_vertex;

        // Enqueue all adjacent vertices of the dequeued vertex
        vertex_t *current = graph->list[current_vertex];
        while (current != NULL) {
            if (!graph->list[current->id]->visited) {
                graph->list[current->id]->visited = true;
                queue_enqueue(queue, current->id);
            }

            current = current->next;
        }
    }

    queue_destroy(queue);
    return bfs_order;
}

#elif defined(GRAPH_MATRIX_H)

int *graph_bfs(graph_matrix_t *graph, int start) {
    assert(graph != NULL);
    assert(start >= 0);
    assert(start < graph->num_vertices);

    // Array to store the order of vertices visited in BFS
    int *bfs_order = (int *)malloc(sizeof(int) * graph->num_vertices);
    int bfs_order_index = 0;

    // Initialize the visited array
    bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));

    queue_t *queue = queue_create();

    // Mark the start vertex as visited and enqueue it
    visited[start] = true;
    queue_enqueue(queue, start);

    while (!queue_is_empty(queue)) {
        // Dequeue a vertex from the queue
        int current_vertex = queue_dequeue(queue);

        // Add the dequeued vertex to the BFS order
        bfs_order[bfs_order_index++] = current_vertex;

        // Enqueue all adjacent vertices of the dequeued vertex
        for (int i = 0; i < graph->num_vertices; ++i) {
            if (graph->matrix[current_vertex][i] && !visited[i]) {
                visited[i] = true;
                queue_enqueue(queue, i);
            }
        }
    }

    free(visited);
    queue_destroy(queue);
    return bfs_order;
}

#endif
