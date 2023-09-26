#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* thread_func(void* arg) {
    printf("Child thread %ld\n", pthread_self());
    pthread_detach(pthread_self());
    pthread_exit(NULL);
}

int main() {
    int err;
    while(true) {
        pthread_t thread;
        err = pthread_create(&thread, NULL, thread_func, NULL);
        if (err) {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return -1;
        }
    }
    return 0;
}
