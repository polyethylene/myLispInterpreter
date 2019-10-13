//
// Created by 聚乙烯 on 2019/10/3.
//

#ifndef SOURCE_MEMORY_POOL_H
#define SOURCE_MEMORY_POOL_H

#define CHUNK_SIZE 4096
#define ITEM_SIZE 256

typedef struct memory_pool memp;
typedef struct memory_chunk memc;
typedef struct memory_item memi;

typedef char BYTE; // sizeof(char) == 1 byte

struct memory_pool {
    memc *first_memc;
    memi *free_memi;
};

struct memory_item {
    memi *next;
    BYTE data[ITEM_SIZE - sizeof(memi *)];
};

struct memory_chunk {
    memc *next;
    memi data[CHUNK_SIZE / ITEM_SIZE];
};

memp *memp_new();

void *memp_alloc(memp *);

void memp_free(memp *, void *);

#endif //SOURCE_MEMORY_POOL_H
