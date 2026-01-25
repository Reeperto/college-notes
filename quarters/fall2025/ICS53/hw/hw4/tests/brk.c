#include "icsmm.h"
#include <stdio.h>

int main() {
    ics_mem_init(NULL);

    void* p1 = ics_malloc(128);
    void* p2 = ics_malloc(128);
    void* p3 = ics_malloc(128);
    ics_buckets_print();
    ics_free(p2);
    ics_buckets_print();
    ics_free(p3);
    ics_buckets_print();
    ics_free(p1);
    ics_buckets_print();

    ics_mem_fini();
}
