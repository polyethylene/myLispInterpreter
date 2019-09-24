#ifndef SOURCE_HASH_TABLE_H
#define SOURCE_HASH_TABLE_H

#define TABLE_SIZE 1000003

typedef void free_func(void *);

typedef struct hash_elem hash_elem;
typedef struct hash_table hash_table;

struct hash_elem {
    hash_elem *next;
    char *key;
    void *elem;

    free_func *elem_free;
};

struct hash_table {
    unsigned int size;
    unsigned int capacity;
    hash_elem **keys;
};

hash_table *hash_table_new();

//void hash_table_extent(hash_table *);

hash_elem *hash_elem_new(char *, void *, free_func *);

void hash_elem_free(hash_elem *);

void hash_table_add(hash_table *, char *, void *, free_func *);

void hash_table_delete(hash_table *, char *);

int hash_table_find(hash_table *, char *);

void *hash_table_get(hash_table *, char *);

void hash_table_free(hash_table *);

#endif //SOURCE_HASH_TABLE_H
