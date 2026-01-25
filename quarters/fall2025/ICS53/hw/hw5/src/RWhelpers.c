#include "RWhelpers.h"

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

void writer_rw_get(sem_t* sem) {
    sem_wait(sem);
}

void writer_rw_release(sem_t* sem) {
    sem_post(sem);
}

void reader_rw_get(pthread_mutex_t* count_mutex, sem_t* sem, int* reader_count) {
    LOCK(count_mutex);
    {
        *reader_count += 1;

        if (*reader_count == 1) {
            sem_wait(sem);
        }
    }
    UNLOCK(count_mutex);
}

void reader_rw_release(pthread_mutex_t* count_mutex, sem_t* sem, int* reader_count) {
    LOCK(count_mutex);
    {
        *reader_count -= 1;

        if (*reader_count == 0) {
            sem_post(sem);
        }
    }
    UNLOCK(count_mutex);
}

void thread_list_push(ThreadList* list, pthread_t tid) {
    if (list->size + 1 > list->cap) {
        list->cap = (list->cap == 0) ? 1 : list->cap * 2;
        list->items = realloc(list->items, list->cap * sizeof(pthread_t));
    }

    list->items[list->size++] = tid;
}

void thread_list_remove(ThreadList* list, int idx) {
    if (list->size == 0) return;

    for (int i = idx; i < list->size - 1; ++i) {
        list->items[i] = list->items[i + 1];
    }

    --list->size;
}

void thread_list_prune(ThreadList* list, bool block) {
    for (int i = list->size - 1; i >= 0; --i) {
        int res;

        if (block) {
            res = pthread_join(list->items[i], NULL);
        } else {
            res = pthread_tryjoin_np(list->items[i], NULL);
        }

        if (res == 0) {
            thread_list_remove(list, i);
        }
    }
}

void thread_list_signal(ThreadList *list, int sig) {
    for (int i = 0; i < list->size; ++i) {
        pthread_kill(list->items[i], sig);
    }
}

void thread_list_destroy(ThreadList *list) {
    free(list->items);
}
