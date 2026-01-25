#ifndef HELPERS_H
#define HELPERS_H

#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define MESSAGE_SIZE (sizeof(message_t))

#define LOCK(m) assert(pthread_mutex_lock((m)) == 0)
#define UNLOCK(m) assert(pthread_mutex_unlock((m)) == 0)

void writer_rw_get(sem_t* sem);
void writer_rw_release(sem_t* sem);
void reader_rw_get(pthread_mutex_t* count_mutex, sem_t* sem, int* reader_count);
void reader_rw_release(pthread_mutex_t* count_mutex, sem_t* sem, int* reader_count);

#define RW_W_GET(sem) writer_rw_get((sem))
#define RW_W_RELEASE(sem) writer_rw_release((sem))
#define RW_R_GET(mut, sem, cnt) reader_rw_get((mut), (sem), (cnt))
#define RW_R_RELEASE(mut, sem, cnt) reader_rw_release((mut), (sem), (cnt))

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
