#include "pmutex.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

PMutex m;

void* worker(void* arg) {
    int id = *(int*)arg;
    int priority = (id % 3) + 1;
    
    pmutex_request(&m, id, priority);
    pmutex_lock(&m, id);
    
    printf("[Work] PID %d\n", id);
    sleep(1);
    
    pmutex_unlock(&m, id);
    return NULL;
}

int main() {
    pmutex_init(&m, 10);
    pthread_t threads[5];
    int ids[5] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
        usleep(10000); // Ensure different timestamps
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pmutex_free(&m);
    return 0;
}
