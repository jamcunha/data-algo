#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct ht_node {
    int             key;
    int             value;
    struct ht_node* next;
} ht_node_t;

typedef struct ht {
    ht_node_t** table;
    int         size;
    int         (*hash)(int key, int size);
} ht_t;

// use your own hash function
void set_hash(ht_t* table, int (*hash)(int key, int size));

ht_t* ht_create(int size);

void ht_insert(ht_t* table, int key, int value);

int ht_delete(ht_t* table, int key);

int ht_search(ht_t* table, int key);

void ht_destroy(ht_t* table);

#endif // HASH_TABLE_H
