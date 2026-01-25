#include "icsmm.h"
#include "debug.h"
#include "helpers4.h"
#include <stdio.h>

void *ics_malloc(size_t size) { 
    if (size == 0) {
        errno = EINVAL;
        return NULL;
    }

    ics_header* block = allocate_block(size);

    if (!block) {
        errno = ENOMEM;
        return NULL;
    }

    return ((void*)block) + sizeof(ics_header);
}

int ics_free(void *ptr) { 
    if (
        (ptr < g_heap_beg + sizeof(ics_footer)) 
        || (ptr >= g_heap_end - sizeof(ics_header))
    ) {
        goto error;
    }

    ics_header* header = ptr - sizeof(ics_header);
    ics_footer* footer = block_get_footer(header);

    if (
        block_is_free(header->block_size) 
        || block_is_free(footer->block_size)
    ) {
        goto error;
    }

    if (header->hid != HEADER_MAGIC || footer->fid != FOOTER_MAGIC) {
        goto error;
    }

    if (header->block_size != footer->block_size) {
        goto error;
    }

    ics_free_header* free_block = block_set_free(header);
    freelist_insert(coalesce(free_block));

    return 0;

error:
    errno = EINVAL;
    return -1;
}
