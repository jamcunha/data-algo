#include "hash_table.h"

#include <stdlib.h>

// NOTE: This is a simple hash function that takes the key and the size of the
// hash table and returns the key modulo the size of the hash table.
// This function is here as an example and it can easily lead to collisions.
static int hash(int key, int size) {
    return key % size;
}

static ht_node_t* ht_node_create(int key, int value) {
    ht_node_t* node = (ht_node_t*)malloc(sizeof(ht_node_t));
    *node = (ht_node_t){
        .key = key,
        .value = value,
        .next = NULL
    };

    return node;
}

void set_hash(ht_t *table, int (*hash)(int, int)) {
    if (table == NULL) {
        return;
    }

    table->hash = hash;
}

ht_t* ht_create(int size) {
    ht_t* ht = (ht_t*)malloc(sizeof(ht_t));
    *ht = (ht_t){
        .size = size,
        .hash = hash,
        .table = (ht_node_t**)malloc(size * sizeof(ht_node_t*))
    };

    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void ht_insert(ht_t* table, int key, int value) {
    if (table == NULL) {
        return;
    }

    int index = table->hash(key, table->size);
    ht_node_t* node = table->table[index];

    // no collision
    if (node == NULL) {
        table->table[index] = ht_node_create(key, value);
        return;
    }

    // Collision resolution
    while (node->next != NULL) {
        node = node->next;
    }

    node->next = ht_node_create(key, value);
}

int ht_delete(ht_t* table, int key) {
    if (table == NULL) {
        return -1;
    }

    int index = table->hash(key, table->size);

    for (ht_node_t* node = table->table[index], *prev = NULL; node != NULL; prev = node, node = node->next) {
        if (node->key == key) {
            if (prev == NULL) {
                table->table[index] = node->next;
            } else {
                prev->next = node->next;
            }

            int value = node->value;
            free(node);
            return value;
        }
    }

    return -1;
}

int ht_search(ht_t* table, int key) {
    if (table == NULL) {
        return -1;
    }

    int index = table->hash(key, table->size);
    for (ht_node_t* node = table->table[index]; node != NULL; node = node->next) {
        if (node->key == key) {
            return node->value;
        }
    }

    return -1;
}

void ht_destroy(ht_t* table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < table->size; i++) {
        ht_node_t* node = table->table[i];
        while (node != NULL) {
            ht_node_t* next = node->next;
            free(node);
            node = next;
        }
    }
    free(table->table);
    free(table);
}
