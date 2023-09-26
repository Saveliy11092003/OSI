#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int global_var;

void *mythread(void *arg) {
	printf("mythread [%d %d %d]: Hello from mythread!\n\n", getpid(), getppid(), gettid());
	return NULL;
}

void *function_for_thread(void *arg) {
	printf("mythread pid - %d, ppid -  %d, gettid -  %d,  pthread_self - %lu]: \n", getpid(), getppid(), gettid(),  pthread_self());
	int local_var;
	static int static_local_var;
	const int const_local_var;

	printf("Local variable address: %p\n", &local_var);
	printf("Static local variable address: %p\n", &static_local_var);
	printf("Constant local variable address: %p\n", &const_local_var);
	printf("Global variable address: %p\n\n", &global_var);
}


int main() {
	pthread_t tid;
	pthread_t tids[5];
	int err;

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

	err = pthread_create(&tid, NULL, mythread, NULL);

	if (err) {
	    printf("main: pthread_create() failed: %s\n", strerror(err));
	    return -1;
	}


	err = pthread_join(tid,NULL);
	if (err) {
            printf("main: pthread_join() failed: %s\n", strerror(err));
            return -1;
        }


	for(int i=0;i<5;i++){
	    err = pthread_create(&tids[i], NULL, function_for_thread, NULL);
            printf("return value of pthread_create - %lu\n", tids[i]);
	    //sleep(1);
	    if (err) {
		printf("main: pthread_join() failed: %s\n", strerror(err));
                return -1;
            }
	}

	for(int i=0;i<5;i++){
	   err = pthread_join(tids[i], NULL);
	   if(err){
		printf("main: pthread_join() failed: %s\n", strerror(err));
	   }
	}

	return 0;
}

