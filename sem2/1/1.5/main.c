#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
void* thread1_func(void* arg) {
    sigset_t set;
    sigfillset(&set);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    printf("Thread 1 blocking all signals\n");
    while(1) {

    }
}

void sigint_handler(int signum) {
    printf("Thread 2 received SIGINT signal\n");
}

void* thread2_func(void* arg) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    printf("Thread 2 waiting for SIGINT signal\n");
    while(1) {
    }
}

void* thread3_func(void* arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    int sig;
    printf("3 thread wait\n");
    sigwait(&set, &sig);
    printf("Thread 3 received SIGQUIT signal\n");
}

void* thread4_func(void* arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    int sig;
    printf("4 thread wait\n");
    sigwait(&set, &sig);
    printf("Thread 4 received SIGQUIT signal\n");
}




int main() {
    pthread_t thread1, thread2, thread3, thread4;
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);
    pthread_create(&thread3, NULL, thread3_func, NULL);
    pthread_create(&thread4, NULL, thread3_func, NULL);

    sleep(2);
    kill(thread1, SIGINT);
    kill(thread2, SIGINT);
    pthread_kill(thread3, SIGQUIT);
    pthread_kill(thread4, SIGINT);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    return 0;
}
