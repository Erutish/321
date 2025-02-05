#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_n 5
#define int_perthread 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_thread = 0;

void* print_integers(void* arg) {
    int thread_number = *(int*)arg;

    pthread_mutex_lock(&mutex);
    while (current_thread != thread_number) {
        pthread_cond_wait(&cond, &mutex);
    }

    int start_number = thread_number * int_perthread + 1;
    for (int i = 0; i < int_perthread; i++) {
        printf("Thread %d prints %d\n", thread_number, start_number + i);
    }

    current_thread++;
    pthread_cond_broadcast(&cond); // Notify all waiting threads
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[thread_n];
    int thread_numbers[thread_n];

    for (int i = 0; i < thread_n; i++) {
        thread_numbers[i] = i; // Assign unique numbers to each thread
        pthread_create(&threads[i], NULL, print_integers, &thread_numbers[i]);
    }

    for (int i = 0; i < thread_n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

