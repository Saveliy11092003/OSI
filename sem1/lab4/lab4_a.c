#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int global_initialized = 42;
int global_uninitialized;
const int global_const = 777;

void foo() {
    int local = 123;
    static int static_local = 456;
    const int const_local = 999;

    printf("Local variable address: %p\n", &local);
    printf("Static local variable address: %p\n", &static_local);
    printf("Const local variable address: %p\n", &const_local);
}

int main() {
    printf("Global initialized variable address: %p\n", &global_initialized);
    printf("Global uninitialized variable address: %p\n", &global_uninitialized);
    printf("Global const variable address: %p\n", &global_const);
    foo();
    printf("pid: %d\n", getpid());
}

