#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void sigint_handler3(int signum) {
    printf("Thread 3 received SIGINT signal\n");
}

void* thread3_func(void* arg) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler3;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    printf("Thread 3 waiting for SIGINT signal\n");
    while(1) {
    }
}

void sigint_handler2(int signum) {
    printf("Thread 2 received SIGINT signal\n");
}

void* thread2_func(void* arg) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler2;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    printf("Thread 2 waiting for SIGINT signal\n");
    while(1) {
    }
}

void sigint_handler1(int signum) {
    printf("Thread 1 received SIGINT signal\n");
}

void* thread1_func(void* arg) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    printf("Thread 1 waiting for SIGINT signal\n");
    while(1) {
    }
}



int main() {
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread3, NULL, thread3_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);
    sleep(2);
    kill(getpid(), SIGINT);
    return 0;
}
