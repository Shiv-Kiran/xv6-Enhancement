#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

int account_balance = 0;
pthread_mutex_t lock ;

void* increment(void * arg) {
    // int* num =(int*)  arg;
    int num = *(int *) arg;
    printf("thread %d \n", num);
    for (int j =0 ;j<num;j++){

        for (int i = 0; i < 1000000; i++) {
            pthread_mutex_lock(&lock);
            account_balance++;
            if(i%1000000 ==0 && j%100 == 0)
                printf("Account balance = %d \n",account_balance);
            pthread_mutex_unlock(&lock);
        }
    }
}

int main(int argc, char* argv[]) {
    if(pthread_mutex_init(&lock, NULL)){
        perror("Couldn't create mutex");
        return 1;
    }
    int threadNum = atoi(argv[1]);
    // scanf("%d", &threadNum);
    pthread_t th[threadNum];
    int i;
    int mill;
    mill = 2048/threadNum;
    for (i = 0; i < threadNum; i++) {
        if (pthread_create(th + i, NULL, &increment, &mill) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Transaction %d has started\n", i);
    }
    for (i = 0; i < threadNum; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Transaction %d has finished\n", i);
    }
    printf("Account Balance is : %d\n", account_balance);
    return 0;
}
