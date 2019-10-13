//
// Created by 聚乙烯 on 2019/10/3.
//

#include "memory_pool.h"
#include <stdlib.h>
#include <stdio.h>

memp *memp_new(unsigned int chk_size, unsigned int itm_size) {
    memp *r = malloc(sizeof(memp));
    r->first_memc = NULL;
    r->free_memi = NULL;
    return r;
}

void *_memp_alloc(memp *mp) {
    if (mp->free_memi == NULL) {
        /* alloc new chunk ( include item list and all item data ) */
        memc *new_chk = malloc(sizeof(memc));

        unsigned item_num = CHUNK_SIZE / ITEM_SIZE;

        for (int i = 0; i < item_num - 1; i++) {
            new_chk->data[i].next = &new_chk->data[i + 1];
        }
        new_chk->data[item_num - 1].next = NULL;
        mp->free_memi = &new_chk->data[0];
    }
    void *r = mp->free_memi;
    mp->free_memi = mp->free_memi->next;
    return r;
}

void _memp_free(memp *mp, void *fi) {
    memi *free_itm = (memi *) fi;
    free_itm->next = mp->free_memi;
    mp->free_memi = free_itm;
}