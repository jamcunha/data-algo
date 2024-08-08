#include "interval_tree.h"
#include <stdlib.h>

static bool do_overlap(interval_t a, interval_t b) {
    return a.low <= b.high && b.low <= a.high;
}

static interval_tree_node_t* create_node(interval_t interval) {
    interval_tree_node_t* node = (interval_tree_node_t*)malloc(sizeof(interval_tree_node_t));
    node->interval = interval;
    node->max = interval.high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void compute_max(interval_tree_node_t* node) {
    int max = node->interval.high;

    if (node->left != NULL && node->left->max > max) {
        max = node->left->max;
    } else if (node->right != NULL && node->right->max > max) {
        max = node->right->max;
    }

    node->max = max;
}

static interval_tree_node_t* insert(interval_tree_node_t* node, interval_t interval) {
    if (node == NULL) {
        return create_node(interval);
    }

    if (interval.low < node->interval.low) {
        node->left = insert(node->left, interval);
    } else {
        node->right = insert(node->right, interval);
    }

    compute_max(node);
    return node;
}

static void search_interval(interval_tree_node_t* node, interval_t interval, interval_t* intervals, int* num_intervals) {
    if (node == NULL) return;

    if (do_overlap(node->interval, interval)) {
        intervals[*num_intervals] = node->interval;
        (*num_intervals)++;
    }

    if (node->left != NULL && node->left->max >= interval.low) {
        search_interval(node->left, interval, intervals, num_intervals);
    } else {
        search_interval(node->right, interval, intervals, num_intervals);
    }
}

static void destroy(interval_tree_node_t* node) {
    if (node == NULL) return;

    destroy(node->left);
    destroy(node->right);
    free(node);
}

interval_tree_t* interval_tree_create(void) {
    interval_tree_t* tree = (interval_tree_t*)malloc(sizeof(interval_tree_t));
    tree->root = NULL;
    return tree;
}

bool interval_tree_insert(interval_tree_t* tree, int low, int high) {
    if (tree == NULL) return false;
    if (low > high) return false;

    interval_t interval = { low, high };
    tree->root = insert(tree->root, interval);
    tree->size++;

    return true;
}

interval_t* interval_tree_search_interval(interval_tree_t* tree, int low, int high, int* num_intervals) {
    if (tree == NULL) return NULL;
    if (low > high) return NULL;

    interval_t* intervals = (interval_t*)malloc(tree->size * sizeof(interval_t));
    if (intervals == NULL) return NULL;
    *num_intervals = 0;

    search_interval(tree->root, (interval_t){ low, high }, intervals, num_intervals);
    return intervals;
}

interval_t* interval_tree_search_point(interval_tree_t* tree, int point, int* num_intervals) {
    if (tree == NULL) return NULL;

    interval_t* intervals = (interval_t*)malloc(tree->size * sizeof(interval_t));
    if (intervals == NULL) return NULL;
    *num_intervals = 0;

    interval_t interval = { point, point };
    search_interval(tree->root, interval, intervals, num_intervals);
    return intervals;
}

void interval_tree_destroy(interval_tree_t *tree) {
    if (tree == NULL) return;

    destroy(tree->root);
    free(tree);
}
