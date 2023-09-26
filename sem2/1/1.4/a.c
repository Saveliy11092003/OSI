#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* print_strings(void* arg) {
    while(1) {
        printf("Hello, world!\n");
    }
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, print_strings, NULL);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
    return 0;
}
