#include "pmutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pmutex_init(PMutex* m, int capacity) {
    m->queue = malloc(capacity * sizeof(Process));
    m->capacity = capacity;
    m->size = 0;
    m->current_holder = -1;
    pthread_mutex_init(&m->lock, NULL);
    pthread_cond_init(&m->cond, NULL);
}

void pmutex_free(PMutex* m) {
    free(m->queue);
    pthread_mutex_destroy(&m->lock);
    pthread_cond_destroy(&m->cond);
}

void pmutex_request(PMutex* m, int pid, int priority) {
    pthread_mutex_lock(&m->lock);
    
    Process p = {
        .pid = pid,
        .priority = priority
    };
    gettimeofday(&p.timestamp, NULL);
    
    m->queue[m->size++] = p;
    printf("[Request] PID %d (Priority %d)\n", pid, priority);
    
    pthread_mutex_unlock(&m->lock);
}

static Process select_winner(PMutex* m) {
    Process winner = m->queue[0];
    
    // Find earliest timestamp
    for (int i = 1; i < m->size; i++) {
        if (timercmp(&m->queue[i].timestamp, &winner.timestamp, <)) {
            winner = m->queue[i];
        }
    }
    
    // Find highest priority among earliest
    for (int i = 0; i < m->size; i++) {
        if (timercmp(&m->queue[i].timestamp, &winner.timestamp, ==) &&
            m->queue[i].priority > winner.priority) {
            winner = m->queue[i];
        }
    }
    
    return winner;
}

void pmutex_lock(PMutex* m, int pid) {
    pthread_mutex_lock(&m->lock);
    
    while (1) {
        if (m->current_holder == -1) {
            Process winner = select_winner(m);
            if (winner.pid == pid) {
                // Remove from queue
                for (int i = 0; i < m->size; i++) {
                    if (m->queue[i].pid == pid) {
                        for (int j = i; j < m->size-1; j++) {
                            m->queue[j] = m->queue[j+1];
                        }
                        m->size--;
                        break;
                    }
                }
                
                m->current_holder = pid;
                printf("[Enter CS] PID %d\n", pid);
                pthread_mutex_unlock(&m->lock);
                return;
            }
        }
        pthread_cond_wait(&m->cond, &m->lock);
    }
}

void pmutex_unlock(PMutex* m, int pid) {
    pthread_mutex_lock(&m->lock);
    
    if (m->current_holder == pid) {
        printf("[Exit CS] PID %d\n", pid);
        m->current_holder = -1;
        pthread_cond_broadcast(&m->cond);
    }
    
    pthread_mutex_unlock(&m->lock);
}
