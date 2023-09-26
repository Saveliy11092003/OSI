#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* thread_func(void* arg) {
    printf("Thread started\n");
    return (void*)42;
}

int main() {
    pthread_t tid;
    int err;
    void* result;
    err = pthread_create(&tid, NULL, thread_func, NULL);

    if (err) {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return -1;
    }


    err = pthread_join(tid,&result);
    if (err) {
        printf("main: pthread_join() failed: %s\n", strerror(err));
        return -1;
    }
    printf("Thread returned %ld\n", (long)result);
    printf("sizeof(void*) - %ld\n", sizeof(void*));
    printf("sizeof(long) - %ld\n", sizeof(long));
    printf("sizeof(int) - %ld\n", sizeof(int));

    return 0;
}

