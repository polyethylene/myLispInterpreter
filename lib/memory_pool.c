//
// Created by 聚乙烯 on 2019/10/14.
//

#include "memory_pool.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void memc_write(memc *mc, void *dest) {
    memcpy(dest, mc, sizeof(memc));
}

void memc_read(memc *mc, void *src) {
    memcpy(mc, src, sizeof(memc));
}

memp *memp_new(DWORD required_tot_size, MP_BOOL if_bound_check) {
    memp *rmp = malloc(sizeof(memp));
    rmp->bound_check = if_bound_check;

    /* malloc whole memory */
    rmp->pool_memory = malloc(required_tot_size);
    rmp->tot_size = required_tot_size;

    if (rmp->bound_check == MP_TRUE) {
        rmp->free_size = required_tot_size - sizeof(memc) - (BOUND_CHECK_SIZE << 1);
        memc tmpc = {
                .next = NULL,
                .prev = NULL,
                .free_chunk = MP_TRUE,
                .data_size = rmp->free_size
        };
        memc_write(&tmpc, rmp->pool_memory + BOUND_CHECK_SIZE);
        memcpy(rmp->pool_memory, start_bound, BOUND_CHECK_SIZE);
        memcpy(rmp->pool_memory + rmp->free_size, end_bound, BOUND_CHECK_SIZE);
    } else {
        rmp->free_size = required_tot_size - sizeof(memc);
        memc tmpc = {
                .next = NULL,
                .prev = NULL,
                .free_chunk = MP_TRUE,
                .data_size = rmp->free_size
        };
        memc_write(&tmpc, rmp->pool_memory);
    }
    return rmp;
}

void memp_del(memp *mp) {
    free(mp->pool_memory);
    free(mp);
}

void *memp_alloc(memp *mp, DWORD memory_size) {
    /* step 1: calculate the total required memory */

    DWORD required_size = memory_size + sizeof(memc);

    /* if free space is not big enough */
    if (mp->free_size < required_size) {
        printf("memp_alloc: not enough space!");
        return NULL;
    }
    memc *tmpc;

    /* if enable bound check, need two more bound size */
    if (mp->bound_check == MP_TRUE) {
        required_size += (BOUND_CHECK_SIZE << 1);
        tmpc = (memc *) (mp->pool_memory + BOUND_CHECK_SIZE);
    } else {
        tmpc = (memc *) mp->pool_memory;
    }

    /* step 2: find the chunk which is big enough */

    while (tmpc) {
        if (tmpc->free_chunk == MP_TRUE && tmpc->data_size >= required_size) {
            break;
        } else {
            tmpc = tmpc->next;
        }
    }

    /* if can't find the big enough chunk */
    if (!tmpc) {
        return NULL;
    }

    BYTE *block_data = (BYTE *) tmpc;

    DWORD free_size = tmpc->data_size - required_size;

    /* Step 3: if the rest size is greater than a chunk size + 64,
     * divide the chunk */
    if (free_size > sizeof(memc) + 64) {
        memc new_chunk = {
                .data_size = free_size,
                .free_chunk = MP_TRUE,
                .next = tmpc->next,
                .prev = tmpc
        };
        BYTE *new_block_data = block_data + required_size;

        /* the begin of new block (exclude the start bound) */
        memc_write(&new_chunk, block_data + required_size);
        if (new_chunk.next) {
            new_chunk.next->prev = (memc *) (new_block_data);
        }
        tmpc->next = (memc *) (new_block_data);
        /* add bound check space */
        mp->free_size -= sizeof(memc);

        if (mp->bound_check == MP_TRUE) {
            memcpy(new_block_data - BOUND_CHECK_SIZE, start_bound, BOUND_CHECK_SIZE);
            mp->free_size -= BOUND_CHECK_SIZE << 1;
        }
        tmpc->next = (memc *) (new_block_data);
        tmpc->data_size = memory_size;
    }
    tmpc->free_chunk = MP_FALSE;
    mp->free_size -= tmpc->data_size;

    /* rewrite the bound between the chunk */

    if (mp->bound_check == MP_TRUE) {
        memcpy(block_data - BOUND_CHECK_SIZE, start_bound, BOUND_CHECK_SIZE);
        memcpy(block_data + required_size - (BOUND_CHECK_SIZE << 1), end_bound, BOUND_CHECK_SIZE);
    }

    /* Step 4: return the arrow */

    return block_data + sizeof(memc);
}

void memp_free(memp *mp, void *ptr) {
    if (!ptr) {
        return;
    }
    memc *tar_chunk = (memc *) (((BYTE *) ptr) - sizeof(memc));
    if (tar_chunk->free_chunk == MP_TRUE) {
        printf("memp_free: space has already free!");
        return;
    }
    mp->free_size += tar_chunk->data_size;
    memc *prev = tar_chunk->prev,
            *next = tar_chunk->next;
    if (prev && prev->free_chunk == MP_TRUE) {
        prev->next = next;
        next->prev = prev;
        prev->data_size += tar_chunk->data_size + sizeof(memc);
        mp->free_size += sizeof(memc);
        if (mp->bound_check == MP_TRUE) {
            prev->data_size += (BOUND_CHECK_SIZE << 1);
            mp->free_size += (BOUND_CHECK_SIZE << 1);
        }
        tar_chunk = prev;
        tar_chunk->free_chunk = MP_TRUE;
    }
    if (next && next->free_chunk == MP_TRUE) {
        tar_chunk->next = next->next;
        if (next->next) {
            next->next->prev = tar_chunk;
        }
        tar_chunk->data_size += next->data_size + sizeof(memc);
        mp->free_size += sizeof(memc);
        if (mp->bound_check == MP_TRUE) {
            tar_chunk->data_size += (BOUND_CHECK_SIZE << 1);
            mp->free_size += (BOUND_CHECK_SIZE << 1);
        }
    }
    tar_chunk->free_chunk = MP_TRUE;
}

void check_each_chunk(memp *mp) {
    int tot_chunk_num = 0, tot_cal_size = 0, tot_cal_free_size = 0;
    memc *tmp_chunk;
    if (mp->bound_check == MP_TRUE) {
        tmp_chunk = (memc *) (mp->pool_memory + BOUND_CHECK_SIZE);
    } else {
        tmp_chunk = (memc *) (mp->pool_memory);
    }
    while (tmp_chunk) {
        printf("chunk %d, free status: %c, chunk size: %d\n",
               tot_chunk_num, (tmp_chunk->free_chunk == MP_TRUE) ? 'Y' : 'N', tmp_chunk->data_size);
        tot_chunk_num++;
        tot_cal_size += tmp_chunk->data_size + sizeof(memc);
        if (tmp_chunk->free_chunk == MP_TRUE) {
            tot_cal_free_size += tmp_chunk->data_size;
        }
        if (mp->bound_check == MP_TRUE) {
            tot_cal_size += BOUND_CHECK_SIZE * 2;
        }
        tmp_chunk = tmp_chunk->next;
    }
    printf("calculate total size: %d, total size %d\n", tot_cal_size, mp->tot_size);
    printf("calculate total free size: %d, total free size %d\n", tot_cal_free_size, mp->free_size);
}