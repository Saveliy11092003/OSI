#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* thread_func(void* arg) {
    printf("Thread started\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int err;

    err = pthread_create(&tid, NULL, thread_func, NULL);

    if (err) {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return -1;
    }


    err = pthread_join(tid,NULL);
    if (err) {
        printf("main: pthread_join() failed: %s\n", strerror(err));
        return -1;
    }

    printf("main finished\n");
    return 0;
}
