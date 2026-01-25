#ifndef HELPERS4_H
#define HELPERS4_H

#include <stdlib.h>
#include <stdbool.h>

#include "icsmm.h"

extern void* g_heap_beg;
extern void* g_heap_end;

size_t block_get_size(void* block);
size_t block_payload_size(ics_header* header);

bool block_is_free(size_t block_size);
ics_free_header* block_set_free(ics_header* block);

ics_footer* block_get_footer(ics_header* header);
ics_header* block_get_header(ics_footer* footer);

void freelist_insert(ics_free_header* free_block);
ics_header* allocate_block(size_t req_size);
ics_free_header* coalesce(ics_free_header* block);

#endif
