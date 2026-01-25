#include "helpers4.h"
#include "debug.h"

#define SPLINTER_SIZE 32
#define NON_PAYLOAD_SIZE (sizeof(ics_footer) + sizeof(ics_header))

void* g_heap_beg = NULL;
void* g_heap_end = NULL;

bool block_is_free(size_t block_size) {
    return (block_size & 0b1) == 0;
}

size_t block_get_size(void* block) {
    return ((ics_header*)block)->block_size & -2;
}

ics_footer* block_get_footer(ics_header* header) {
    size_t block_size = block_get_size(header);
    ics_footer* footer = ((void*)header) + block_size - sizeof(ics_footer);

    return footer;
}

ics_header* block_get_header(ics_footer* footer) {
    size_t block_size = block_get_size(footer);
    ics_header* header = (void*)(footer) + sizeof(ics_footer) - block_size;

    return header;
}

ics_footer* block_prev(ics_header* block) {
    return (void*)(block) - sizeof(ics_footer);
}

ics_header* block_next(ics_footer* footer) {
    return (void*)(footer) + sizeof(ics_footer);
}

bool block_is_prologue(ics_footer* block) {
    return (block_get_size(block) == 0) 
        && (!block_is_free(block->block_size))
        && block->requested_size == 0;
}

bool block_is_epilogue(ics_header* block) {
    return (block_get_size(block) == 0) 
        && (!block_is_free(block->block_size));
}

size_t block_payload_size(ics_header* header) {
    assert(header->block_size >= NON_PAYLOAD_SIZE);
    return block_get_size(header) - NON_PAYLOAD_SIZE;
}

ics_bucket* find_bucket(size_t block_size) {
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        if (block_size <= seg_buckets[i].max_size) {
            return &seg_buckets[i];
        }
    }

    assert(false);
}

size_t align_to_16(size_t size) {
    size_t res = 16;

    while (size > res) {
        res += 16;
    }

    return res;
}

ics_free_header* block_set_free(ics_header* block) {
    ics_free_header* free_block = (ics_free_header*)(block);

    free_block->header.block_size &= -2;
    block_get_footer(block)->block_size &= -2;

    free_block->next = NULL;
    free_block->prev = NULL;

    return free_block;
}

ics_header* block_set_allocated(ics_free_header* free_block, size_t req_size) {
    ics_header* block = (ics_header*)(free_block);
    ics_footer* footer = block_get_footer(block);

    block->block_size |= 0b1;
    footer->block_size |= 0b1;
    footer->requested_size = req_size;

    return block;
}

void unlink_free_block(ics_free_header* block) {
    if (block->prev) {
        block->prev->next = block->next;
    } else {
        ics_bucket* bucket = find_bucket(block_get_size(block));
        bucket->freelist_head = block->next;
    }

    if (block->next) {
        block->next->prev = block->prev;
    }

    block->prev = NULL;
    block->next = NULL;
}

// Takes in a block before it enters the freelist and attempts to coalesce in
// both directions, returning the original or coalesced block
ics_free_header* coalesce(ics_free_header* block) {
    ics_free_header* prev = NULL;
    ics_free_header* next = NULL;
    ics_footer* footer = block_get_footer(&block->header);

    ics_footer* prev_block = block_prev(&block->header);

    if (block_is_prologue(prev_block)) {
        prev = block;
    } else {
        ics_header* prev_header = block_get_header(prev_block);

        if (block_is_free(prev_header->block_size)) {
            prev = (ics_free_header*)prev_header;
        } else {
            prev = block;
        }
    }

    ics_header* next_block = block_next(block_get_footer(&block->header));

    if (block_is_epilogue(next_block)) {
        next = block;
    } else {
        if (block_is_free(next_block->block_size)) {
            next = (ics_free_header*)(next_block);
            footer = block_get_footer(next_block);
        } else {
            next = block;
        }
    }

    assert(prev && next);

    if (prev == next) {
        assert(prev == block && next == block);
        return prev;
    }

    if (prev != block) {
        unlink_free_block(prev);
    }

    if (next != block) {
        unlink_free_block(next);
    }

    size_t size = ((void*)(footer) + sizeof(ics_footer)) - (void*)(prev);

    prev->header.block_size = size;
    footer->block_size = size;

    return prev;
}

void freelist_insert(ics_free_header* free_block) {
    ics_bucket* bucket = find_bucket(block_get_size(&free_block->header));

    free_block->next = bucket->freelist_head;

    if (bucket->freelist_head) {
        bucket->freelist_head->prev = free_block;
    }

    bucket->freelist_head = free_block;
}

void init_heap() {
    g_heap_beg = ics_inc_brk();
    g_heap_end = ics_get_brk();
    assert(g_heap_beg && g_heap_end);

    ics_footer* prologue = g_heap_beg;
    ics_header* epilogue = g_heap_end - sizeof(ics_header);

    *prologue = (ics_footer){
        .fid = FOOTER_MAGIC,
        .requested_size = 0,
        .block_size = 0b1
    };

    *epilogue = (ics_header){
        .hid = HEADER_MAGIC,
        .block_size = 0b1
    };

    ics_free_header* header = g_heap_beg + sizeof(ics_footer);
    ics_footer* footer = (void*)(epilogue) - sizeof(ics_footer);

    size_t block_size = (void*)(epilogue) - (void*)(header);

    *header = (ics_free_header){
        .header = {
            .hid = HEADER_MAGIC,
            .block_size = block_size
        },
        .prev = NULL,
        .next = NULL,
    };

    *footer = (ics_footer){
        .fid = FOOTER_MAGIC,
        .block_size = block_size,
        .requested_size = 0
    };

    freelist_insert(header);
}

bool heap_is_empty() {
    bool empty_heap = true;
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        if (seg_buckets[i].freelist_head) {
            empty_heap = false;
            break;
        }
    }

    return empty_heap;
}

bool grow_heap() {
    if (ics_inc_brk() == (void*)(-1) || errno == ENOMEM) {
        return false;
    }

    ics_free_header* new_block = g_heap_end - sizeof(ics_footer);
    g_heap_end = ics_get_brk();
    ics_footer* new_epilogue = g_heap_end - sizeof(ics_footer);

    *new_epilogue = (ics_footer){
        .block_size = 0b1,
        .requested_size = 0,
        .fid = FOOTER_MAGIC
    };

    *new_block = (ics_free_header){
        .header = {
            .block_size = (void*)(new_epilogue) - (void*)(new_block),
            .hid = HEADER_MAGIC,
        },
        .prev = NULL,
        .next = NULL
    };

    freelist_insert(coalesce(new_block));

    return true;
}

ics_free_header* split_free_block(ics_free_header* block, size_t payload_size) {
    assert(payload_size % 16 == 0 && block_get_size(block) >= 32);
    unlink_free_block(block);

    size_t orig_size = block_get_size(block);
    ics_footer* top_footer = block_get_footer(&block->header);

    ics_free_header* top_header = (void*)(block) + NON_PAYLOAD_SIZE + payload_size;
    ics_footer* bot_footer = (void*)(block) + sizeof(ics_header) + payload_size;

    size_t top_size = orig_size - payload_size - NON_PAYLOAD_SIZE;

    *top_footer = (ics_footer){
        .fid = FOOTER_MAGIC,
        .block_size = top_size,
        .requested_size = 0
    };

    *top_header = (ics_free_header){
        .header = {
            .hid = HEADER_MAGIC,
            .block_size = top_size
        },
        .next = NULL,
        .prev = NULL
    };

    size_t bot_size = payload_size + NON_PAYLOAD_SIZE;

    *bot_footer = (ics_footer){
        .fid = FOOTER_MAGIC,
        .block_size = bot_size,
        .requested_size = 0
    };

    *block = (ics_free_header){
        .header = {
            .hid = HEADER_MAGIC,
            .block_size = bot_size
        },
        .prev = NULL,
        .next = NULL
    };

    freelist_insert(top_header);

    return block;
}

ics_free_header* find_free_block(size_t size, bool* is_unlinked) {
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        ics_free_header* candidate = NULL;

        if (size <= seg_buckets[i].max_size) {
            for (
                ics_free_header* p = seg_buckets[i].freelist_head;
                p != NULL;
                p = p->next
            ) {
                if (size <= block_payload_size(&p->header)) {
                    candidate = p;
                    break;
                }
            }
        }

        if (!candidate) { 
            continue; 
        }

        if (block_payload_size(&candidate->header) - size >= SPLINTER_SIZE) {
            candidate = split_free_block(candidate, size);
            *is_unlinked = true;
        } else {
            *is_unlinked = false;
        }

        return candidate;
    }

    return NULL;
}

// We assume that size is a multiple of 16
ics_header* allocate_block(size_t req_size) {
    size_t size = align_to_16(req_size);
    assert(size % 16 == 0);

    if (heap_is_empty()) {
        init_heap();
    }

    while (true) {
        bool block_is_unlinked;
        ics_free_header* block = find_free_block(size, &block_is_unlinked);

        if (!block) { 
            if (!grow_heap()) {
                return NULL;
            } 

            continue;
        }

        if (!block_is_unlinked) {
            unlink_free_block(block);
        }

        block_set_allocated(block, req_size);

        return (ics_header*)(block);
    }
}
