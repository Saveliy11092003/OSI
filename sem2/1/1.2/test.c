#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    printf("Child thread %ld\n", (long)pthread_self());
    pthread_exit(NULL);
}

int main() {
    while(1) {
        pthread_t thread;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&thread, &attr, thread_func, NULL);
    }
    return 0;
}
