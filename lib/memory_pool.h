#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#define BOUND_CHECK_SIZE 8

typedef char BYTE; // sizeof(char) == 1 byte
typedef unsigned long DWORD;// sizeof(unsigned long) == 4 byte


typedef struct memory_pool memp;
typedef struct memory_chunk memc;

static const BYTE start_bound[BOUND_CHECK_SIZE] = {};
static const BYTE end_bound[BOUND_CHECK_SIZE] = {};

/* bool type in memp */
typedef enum {
    MP_TRUE, MP_FALSE
} MP_BOOL;

struct memory_pool {
    DWORD tot_size;
    DWORD free_size;
    MP_BOOL bound_check;
    BYTE *pool_memory;
};

struct memory_chunk {
    memc *next;
    memc *prev;
    MP_BOOL free_chunk;
    DWORD data_size; // real size of the data in chunk (exclude memc space)
};

/* read and write of chunk */

void memc_write(memc *, void *);

void memc_read(memc *, void *);

/* new and del of pool */

memp *memp_new(DWORD, MP_BOOL);

void memp_del(memp *);

void *memp_alloc(memp *, DWORD);

void memp_free(memp *, void *);

/* check function */

void check_each_chunk(memp *);

#endif //MEMORY_POOL_H
