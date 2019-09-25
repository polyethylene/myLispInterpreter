#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(unsigned int x) {
    unsigned int i = 3;
    while (1) {
        unsigned int q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 2;
    }
    return 1;
}

unsigned int next_prime(unsigned int x) {
    if (x <= 2)
        return 2;
    if (!(x & 1))
        ++x;
    while (!is_prime(x)) {
        x += 2;
    }
    return x;
}

unsigned int time33(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + hash + *str++;
    }
    return hash;
}

/* suppose the argument will not be the head of the list */
/* doesn't free the memory */

hash_elem *hash_elem_delete(hash_elem *t) {
    if (!t) {
        return NULL;
    }
    hash_elem *nt = t->next;
    hash_elem *pt = t->prev;
    pt->next = nt;
    if (nt) {
        nt->prev = pt;
    }
    return nt;
}

void hash_elem_insert(hash_elem *d, hash_elem *t) {
    if (!d) {
        return;
    }
    hash_elem *tmp = d->next;
    d->next = t;
    t->prev = d;
    if (tmp) {
        t->next = tmp;
        tmp->prev = t;
    }
}

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

void hash_table_extent(hash_table *ht) {
    unsigned int oc = ht->capacity;
    ht->capacity = next_prime(oc * 2);
    ht->keys = realloc(ht->keys, sizeof(hash_elem *) * ht->capacity);
    for (int i = oc; i < ht->capacity; i++) {
        ht->keys[i] = NULL;
    }

    /* rehash all element */
    for (int i = 0; i < oc; i++) {
        if (ht->keys[i]) {
            hash_elem *tmp = ht->keys[i]->next;

            /* deal with other element */
            while (tmp) {
                if (time33(tmp->key) % ht->capacity != i) {
                    hash_elem *dtmp = tmp;
                    ht->size--;
                    hash_table_add(ht, tmp->key, tmp->elem, tmp->elem_free);
                    tmp = hash_elem_delete(dtmp);
                    free(dtmp->key);
                    free(dtmp);
                } else {
                    tmp = tmp->next;
                }
            }

            /* deal with the first element */
            tmp = ht->keys[i];
            if (time33(tmp->key) % ht->capacity != i) {
                ht->size--;
                hash_table_add(ht, tmp->key, tmp->elem, tmp->elem_free);
                ht->keys[i] = tmp->next;
                if (tmp->next) {
                    tmp->next->prev = NULL;
                }
                free(tmp->key);
                free(tmp);
            }
        }
    }
}


/* suppose v is a copy element and only is used in hash_table */

hash_elem *hash_elem_new(char *k, void *v, free_func *f) {
    hash_elem *r = malloc(sizeof(hash_elem));
    r->key = malloc(strlen(k) + 1);
    strcpy(r->key, k);
    r->elem = v;
    r->next = NULL;
    r->prev = NULL;
    r->elem_free = f;
    return r;
}

void hash_elem_free(hash_elem *e) {
    e->elem_free(e->elem);
    free(e->key);
    free(e);
}

int hash_table_find(hash_table *ht, char *k) {
    unsigned key = time33(k) % (ht->capacity);
    hash_elem *tmp = ht->keys[key];
    while (tmp) {
        if (strcmp(tmp->key, k) == 0) {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void *hash_table_get(hash_table *ht, char *k) {
    unsigned key = time33(k) % (ht->capacity);
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
    ht->size++;
    if (ht->size >= ht->capacity * 0.5) {
        hash_table_extent(ht);
    }
    unsigned key = time33(k) % (ht->capacity);
    if (!ht->keys[key]) {
        ht->keys[key] = hash_elem_new(k, v, f);
        return;
    } else {
        hash_elem *tmp = ht->keys[key];
        while (tmp) {
            if (strcmp(k, tmp->key) == 0) {
                tmp->elem_free(tmp->elem);
                tmp->elem = v;
                tmp->elem_free = f;
                ht->size--;
                return;
            }
            tmp = tmp->next;
        }
        hash_elem *h = hash_elem_new(k, v, f);
        hash_elem_insert(ht->keys[key], h);
    }
}

void hash_table_delete(hash_table *ht, char *k) {
    unsigned int key = time33(k) % (ht->capacity);
    if (!ht->keys[key]) {
        return; // element not exists
    } else {
        hash_elem *tmp = ht->keys[key];

        /* target is the first element of the list */
        if (strcmp(k, tmp->key) == 0) {
            ht->keys[key] = tmp->next;
            if (tmp->next) {
                tmp->next->prev = NULL;
            }
            hash_elem_free(tmp);
            ht->size--;
            return;
        }
        tmp = tmp->next;
        while (tmp) {
            if (strcmp(k, tmp->key) == 0) {
                hash_elem_delete(tmp);
                ht->size--;
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

int count_crush(hash_table *ht) {
    int ret = 0;
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->keys[i]) {
            hash_elem *tmp = ht->keys[i]->next;
            while (tmp) {
                ret++;
                tmp = tmp->next;
            }
        }
    }
    return ret;
}

