#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void free_memory(void* ptr) {
    free(ptr);
}

void* print_string(void* arg) {
    char* str = malloc(12);
    strcpy(str, "hello world");
    pthread_cleanup_push(free_memory, str);
    while(1) {
        printf("%s\n", str);
    }
    pthread_cleanup_pop(1);
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, print_string, NULL);
    sleep(2);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
    return 0;
}
