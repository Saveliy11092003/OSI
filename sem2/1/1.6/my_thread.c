#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PAGE 4096
#define STACK_SIZE 3*PAGE

typedef void *(*start_routine_t) (void *);

typedef struct _mythread {
    int mythread_id;
    void *arg;
    start_routine_t start_routine;
    void *retval;
    volatile int finished;
    volatile int joined;
} mythread_struct_t;

typedef mythread_struct_t* mythread_t;


int thread_startup(void *arg) {
    //printf("before mythread_t tid = (mythread_t)arg;\n");
    //printf("after mythread_t tid = (mythread_t)arg;\n");
    mythread_struct_t* thread = arg;
    //printf("after mythread_struct_t *thread = tid;\n");
    void* retval;

    //printf("sizeof(mythread_struct_t) - %ld\n", sizeof(mythread_struct_t));
    //printf("sizeof(mythread_t) - %ld\n", sizeof(mythread_t));
    //printf("sizeof(void*) - %ld\n", sizeof(void*));

    //printf("after retval\n");
    //printf("111111\n");
    //printf("%d", thread->mythread_id);
    //sleep(5);
    printf("thread_startup: starting a thread function for the thread %d\n",thread->mythread_id);
    //printf("222222");

    retval = thread->start_routine(thread->arg);

    thread->retval = retval;
    thread->finished = 1;

    printf("thread_startup: waiting for join() the thread%d\n", thread->mythread_id);
    while(!thread->joined){
	sleep(1);
    }
    printf("thread_startup: the thread function finished for the thread %d\n", thread->mythread_id);

    return 0;
}

void* create_stack(off_t size, int mytid) {
    char stack_file[128];
    int stack_fd;
    void *stack;

    snprintf(stack_file, sizeof(stack_file), "stack-%d", mytid);

    stack_fd = open(stack_file, O_RDWR | O_CREAT, 0660);

    if(stack_fd == -1){
	printf("stack_fd\n");
    }
    int ft = ftruncate(stack_fd, 0);

    if(ft == -1){ 
        printf("ftruncate 0\n");
    }
    ft = ftruncate(stack_fd, size);

    if(ft == -1){ 
        printf("ftruncate 0\n");
    }


    stack = mmap(NULL, size, PROT_NONE, MAP_SHARED, stack_fd, 0);

    if (stack == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(stack_fd);

    return stack;
}


int mythread_create(mythread_t *mytid, void *(start_routine) (void *), void *arg) {
    static int mythread_id = 0;
    mythread_t thread;
    int child_pid;
    void *child_stack;

    mythread_id++;

    printf("mythread_create: creating thread %d\n", mythread_id);

    child_stack = create_stack(STACK_SIZE, mythread_id);

    mprotect(child_stack + PAGE, STACK_SIZE - PAGE, PROT_READ|PROT_WRITE);

    memset(child_stack + PAGE, 0x7f, STACK_SIZE - PAGE);

    thread = (mythread_struct_t*)(child_stack + STACK_SIZE - sizeof(mythread_struct_t));
    thread->mythread_id = mythread_id;
    thread->arg = arg;
    thread->start_routine = start_routine;
    thread->retval = NULL;
    thread->finished = 0;
    thread->joined = 0;

    child_stack = (void *)thread;

    printf("child stack %p; mythread_struct %p; \n", child_stack, thread);

    //printf("cloning1\n");

    child_pid = clone(thread_startup, child_stack, CLONE_VM | CLONE_FILES | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, (void*)thread);

    //printf("cloning2\n");

    if(child_pid == -1) {
	printf("clone failed %s\n", strerror(errno));
	exit(-1);
    }

    *mytid = thread;
    //printf("after *mytid = tread\n");
    return 0;
}

void mythread_join(mythread_t mytid, void **retval) {
    mythread_struct_t *thread = mytid;

    printf("thread_join: waiting for the thread %d to finish\n", thread->mythread_id);

    while(!thread->finished){
	sleep(1);
    }

    printf("thread_join: the thread %d finished\n", thread->mythread_id);

    *retval = thread->retval;

    thread->joined = 1;
}


void *mythread(void *arg) {
    //printf("mythread starting\n");
    char *str = (char*) arg;

    for(int i=0; i<10; i++) {
	printf("hello from my thread '%s'\n", str);
	sleep(1);
    }

    return "bay";
}


int main() {
    mythread_t mytid;
    void *retval;

    printf("main [%d %d %d]\n", getpid(), getppid(), gettid());

    int return_value_create = mythread_create(&mytid, mythread, "hello from main");

    if(return_value_create == 1) {
	printf("error in mythread_create");
    }

    mythread_join(mytid, &retval);

    printf("main [%d %d %d] thread returned '%s'\n", getpid(), getppid(), gettid(), (char*)retval);

    return 0;
}
