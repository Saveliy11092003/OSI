#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int global_var;

void *function_for_thread(void *arg) {
	printf("2\n");
        int local_var;
	printf("tid - %d\n", gettid());
	printf("local variable address - %p\n", &local_var);
	printf("local_var value - %d\n", local_var);
	printf("global_var value - %d\n\n", global_var);
        static int static_local_var;
        const int const_local_var;

	local_var++;
	global_var++;
}


int main() {

        pthread_t tids[5];
        int err;
	printf("pid - %d\n",getpid());

	for(int i=0;i<5;i++){
	    printf("1\n");
            err = pthread_create(&tids[i], NULL, function_for_thread, NULL);
            printf("return value of pthread_create - %lu\n", tids[i]);
            sleep(1);
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
	sleep(60);
        return 0;
}

