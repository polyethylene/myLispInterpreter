#ifndef SOURCE_HASH_TABLE_H
#define SOURCE_HASH_TABLE_H

#define TABLE_SIZE 4

typedef void free_func(void *);

typedef void *copy_func(void *);

typedef struct hash_elem hash_elem;
typedef struct hash_table hash_table;

struct hash_elem {
    hash_elem *next;
    hash_elem *prev;
    char *key;
    void *elem;

    copy_func *elem_copy;
    free_func *elem_free;

};

struct hash_table {
    unsigned int size;
    unsigned int capacity;
    hash_elem **keys;
};

hash_elem *hash_elem_copy(hash_elem *);

hash_elem *hash_elem_new(char *, void *, free_func *, copy_func *);

void hash_elem_free(hash_elem *);

/* hash_table operation */

hash_table *hash_table_new(unsigned int);

void hash_table_add(hash_table *, char *, void *, free_func *, copy_func *);

void hash_table_delete(hash_table *, char *);

int hash_table_find(hash_table *, char *);

void *hash_table_get(hash_table *, char *);

void hash_table_free(hash_table *);

hash_table *hash_table_copy(hash_table *);

int count_crush(hash_table *);

#endif //SOURCE_HASH_TABLE_H
