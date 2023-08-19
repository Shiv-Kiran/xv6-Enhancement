#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Global variables
#define QUEUE_COUNT 20
long sum = 0;
long odd = 0;
long even = 0;
long min = INT_MAX;
long max = INT_MIN;
bool done = false;

int taskQueue[QUEUE_COUNT];
int taskCount = 0;
int front = 0, rear = 0;

pthread_mutex_t queueMutex;
pthread_mutex_t taskMutex;

void processtask(long number);
void *workerFunc(void *args);
void masterFunc(int);
int queue_delete();
void queue_insert();

void processtask(long number)
{
    // simulate burst time
    sleep(number);

    // update global variables
    pthread_mutex_lock(&taskMutex);
    sum += number;
    if (number % 2 == 1)
    {
        odd++;
    }
    else
    {
        even++;
    }
    if (number < min)
    {
        min = number;
    }
    if (number > max)
    {
        max = number;
    }
    pthread_mutex_unlock(&taskMutex);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sum <infile>\n");
        exit(EXIT_FAILURE);
    }
    char *fn = argv[1];
    // Read from file
    FILE *fin = fopen(fn, "r");
    long t;
    fscanf(fin, "%ld\n", &t);
    printf("The number of tasks are : %ld \n", t);
    int noThreads = (int)t / 2;
    pthread_t threads[noThreads];

    pthread_mutex_init(&queueMutex, NULL);
    pthread_mutex_init(&taskMutex, NULL);
    char type;
    long num;
    for (int i = 0; i < noThreads; i++)
    {
        if (pthread_create(&threads[i], NULL, &workerFunc, NULL) != 0)
        {
            printf("Error could not create thread %d \n", i);
            exit(EXIT_FAILURE);
        }
    }

    while (fscanf(fin, "%c %ld\n", &type, &num) == 2)
    {
        if (type == 'p')
        { // processing task
            /*
            Increases the processCount and call taskInsert
            */
            masterFunc(num);
            printf("Task completed\n");
        }
        else if (type == 'w')
        { // waiting period
            sleep(num);
            printf("Wait Over\n");
        }
        else
        {
            printf("ERROR: Type Unrecognizable: '%c'\n", type);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fin);
    done = true;

    for (int i = 0; i < noThreads; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Error could reap thread %d \n", i);
            exit(EXIT_FAILURE);
        }
    }
    // Print global variables
    printf("%ld %ld %ld %ld %ld\n", sum, odd, even, min, max);

    return (EXIT_SUCCESS);
}

void *workerFunc(void *args)
{
    while (true)
    {
        int item, found = false;
        pthread_mutex_lock(&queueMutex);
        if (taskCount > 0)
        {
            found = true;
            item = queue_delete();
            taskCount--;
        }
        pthread_mutex_unlock(&queueMutex);

        if (found)
        {
            processtask(item);
        }
        if (done == true && taskCount == 0)
            break; // break out of the while loop when everything is completed
    }
    return NULL;
}

void masterFunc(int item)
{
    pthread_mutex_lock(&queueMutex);
    queue_insert(item);
    taskCount++;
    pthread_mutex_unlock(&queueMutex);
}

void queue_insert(int item)
{
    rear = (rear + 1) % QUEUE_COUNT;
    if (front == rear)
    {
        printf("Queue Full \n");
        if (rear == 0)
            rear = QUEUE_COUNT - 1;
        else
            rear--;
    }
    else
        taskQueue[rear] = item;
}

int queue_delete()
{
    int item;
    if (front == rear)
    {
        printf("Queue is empty \n");
    }
    else
    {

        front = (front + 1) % QUEUE_COUNT;
        int item = taskQueue[front];
        return item;
    }
}