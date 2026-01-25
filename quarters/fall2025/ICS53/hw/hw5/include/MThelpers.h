#ifndef HELPERS_H
#define HELPERS_H

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>

#include "protocol.h"

#define MESSAGE_SIZE (sizeof(message_t))

#define LOCK(m) assert(pthread_mutex_lock((m)) == 0)
#define UNLOCK(m) assert(pthread_mutex_unlock((m)) == 0)

typedef struct {
    pthread_t* items;
    int size;
    int cap;
} ThreadList;

void thread_list_push(ThreadList* list, pthread_t tid);
void thread_list_prune(ThreadList* list, bool block);
void thread_list_signal(ThreadList* list, int sig);
void thread_list_destroy(ThreadList* list);

#endif
