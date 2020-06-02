#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t a_lock;
pthread_mutex_t b_lock;
int a = 0, b = 0;

void *taskA(void *args) 
{
    pthread_mutex_lock(&a_lock);
    printf("[taskA]: lock a\n");
    sleep(2);
    a++;
    pthread_mutex_lock(&b_lock);
    printf("lock b\n");
    b += a;
    pthread_mutex_unlock(&b_lock);
    printf("unlock b\n");
    pthread_mutex_unlock(&a_lock);
    printf("unlock a\n");
}

void *taskB(void *args) 
{
    pthread_mutex_lock(&b_lock);
    printf("[taskB]: lock b\n");
    sleep(2);
    b++;
    pthread_mutex_lock(&a_lock);
    printf("lock a\n");
    a += b;
    pthread_mutex_unlock(&b_lock);
    printf("unlock b\n");
    pthread_mutex_unlock(&a_lock);
    printf("unlock a\n");
}

int main() 
{
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, taskA, NULL);
    pthread_create(&threads[1], NULL, taskB, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    printf("[main]: a - %i\n[main]: b - %i\n", a, b);
    return 0;
}