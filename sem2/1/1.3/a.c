#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


struct Data {
    int number;
    char* text;
};

void* print_struct(void* arg) {

    struct Data* data = (struct Data*)arg;

    printf("Number: %d\n", data->number);
    printf("Text: %s\n", data->text);

    pthread_exit(NULL);
}

int main() {

    struct Data data;
    data.number = 42;
    data.text = "Hello, world!";
    int err;
    pthread_t thread;
       pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    err = pthread_create(&thread, &attr, print_struct, (void*)&data);
    if (err) {
        printf("main: pthread_create() failed: %s\n", strerror(err));
        return -1;
    }

    return 0;
}

