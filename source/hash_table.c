#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

hash_table *hash_table_new() {
    hash_table *r = malloc(sizeof(hash_table));
    r->keys = malloc(TABLE_SIZE * sizeof(hash_elem *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        r->keys[i] = NULL;
    }
    r->size = 0;
    r->capacity = TABLE_SIZE;
    return r;
}

/*

void hash_table_extent(hash_table *ht) {
    ht->capacity *= 2;
    ht->keys = realloc(ht->keys, sizeof(hash_elem *) * ht->capacity);
    for (int i = ht->capacity / 2; i < ht->capacity; i++) {
        ht->keys[i] = NULL;
    }
}

*/

/* suppose v is a copy element and only is used in hash_table */

hash_elem *hash_elem_new(char *k, void *v, free_func *f) {
    hash_elem *r = malloc(sizeof(hash_elem));
    r->key = malloc(strlen(k) + 1);
    strcpy(r->key, k);
    r->elem = v;
    r->next = NULL;
    r->elem_free = f;
    return r;
}

void hash_elem_free(hash_elem *e) {
    e->elem_free(e->elem);
    free(e->key);
    free(e);
}

unsigned int time33(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + hash + *str++;
    }
    return hash;
}

int hash_table_find(hash_table *ht, char *k) {
    unsigned key = time33(k) % (ht->capacity);
    return ht->keys[key] != NULL;
}

void *hash_table_get(hash_table *ht, char *k) {
    unsigned key = time33(k) % TABLE_SIZE;
    if (!ht->keys[key]) {
        return NULL;
    } else {
        if (!ht->keys[key]->next) {
            return ht->keys[key]->elem;
        } else {
            hash_elem *tmp = ht->keys[key];
            while (tmp) {
                if (strcmp(tmp->key, k) == 0) {
                    return tmp->elem;
                }
                tmp = tmp->next;
            }
            return NULL;
        }
    }
}

/* suggest v is a copy value */
void hash_table_add(hash_table *ht, char *k, void *v, free_func *f) {
    unsigned key = time33(k) % (ht->capacity);
    if (!ht->keys[key]) {
        ht->keys[key] = hash_elem_new(k, v, f);
        ht->size++;
        /*
        if (ht->size >= ht->capacity * 0.5) {
            hash_table_extent(ht);
        }
         */
        return;
    } else {
        hash_elem *tmp = ht->keys[key];
        while (tmp) {
            if (strcmp(k, tmp->key) == 0) {
                tmp->elem_free(tmp->elem);
                tmp->elem = v;
                tmp->elem_free = f;
                return;
            }
            tmp = tmp->next;
        }
        hash_elem *h = hash_elem_new(k, v, f);
        tmp = ht->keys[key];
        hash_elem *tmp2 = tmp->next;
        tmp->next = h;
        h->next = tmp2;
        count++;
    }
}

void hash_table_delete(hash_table *ht, char *k) {
    unsigned key = time33(k) % (ht->capacity);
    if (ht->keys[key]) {
        return;
    } else {
        hash_elem *tmp = ht->keys[key];
        while (tmp) {
            if (strcmp(k, tmp->key) == 0) {
                hash_elem_free(tmp->elem);
                return;
            }
            tmp = tmp->next;
        }
    }
}

void hash_table_free(hash_table *ht) {
    hash_elem *tmp = NULL;
    hash_elem *tmpnxt = NULL;
    for (int i = 0; i < ht->capacity; i++) {
        tmp = ht->keys[i];
        while (tmp) {
            tmpnxt = tmp->next;
            hash_elem_free(tmp);
            tmp = tmpnxt;
        }
    }
    free(ht);
}