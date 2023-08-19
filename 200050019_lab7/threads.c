#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

int x = 2;

void* foo() {
    printf("You are in foo \n");
    x += 5;
    printf("PID of Foo: %d \n",getpid());
    printf("PthreadID : %lu \n", pthread_self());
    printf("Value of x: %d \n", x);
}

void* bar() {
    printf("You are in bar \n");
    sleep(2);
    printf("PID of Bar: %d \n",getpid());
    printf("PthreadID : %lu \n", pthread_self());
    printf("Value of x: %d \n", x);    
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t2, NULL, &bar, NULL)) {
        return 2;
    }
    if (pthread_create(&t1, NULL, &foo, NULL)) {
        return 1;
    }
    if (pthread_join(t1, NULL)) {
        return 3;
    }
    if (pthread_join(t2, NULL)) {
        return 4;
    }
    return 0;
}