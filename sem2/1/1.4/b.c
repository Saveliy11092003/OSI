#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg) {
    int *counter = (int*) arg;
    int *oldstate;
    while (1) {
        (*counter)++;
	//pthread_testcancel();
	sleep(1);
	//pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, oldstate);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int counter = 0;
    pthread_create(&thread, NULL, threadFunction, (void*)&counter);

    pthread_cancel(thread);

    pthread_join(thread, NULL);

    printf("Counter: %d\n", counter);

    return 0;
}
