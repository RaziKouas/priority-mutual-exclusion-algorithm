#ifndef PMUTEX_H
#define PMUTEX_H

#include <pthread.h>
#include <sys/time.h>

typedef struct {
    int pid;
    int priority;
    struct timeval timestamp;
} Process;

typedef struct {
    Process* queue;
    int size;
    int capacity;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int current_holder;
} PMutex;

void pmutex_init(PMutex* m, int capacity);
void pmutex_free(PMutex* m);
void pmutex_request(PMutex* m, int pid, int priority);
void pmutex_lock(PMutex* m, int pid);
void pmutex_unlock(PMutex* m, int pid);

#endif
