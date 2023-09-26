#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* thread_func(void* arg) {
    printf("Child thread %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    while(true) {
	int err;
        pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        err = pthread_create(&thread, &attr, thread_func, NULL);
        if (err) {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return -1;
        }
    }
    return 0;
}
