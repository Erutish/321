#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function executed by each thread
void *thread_function(void *arg) {
    int thread_num = *(int *)arg;
    printf("thread-%d running\n", thread_num);
    sleep(1); // Simulate work with sleep
    printf("thread-%d closed\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[5]; // Array to hold thread IDs
    int thread_ids[5];    // Array to hold thread numbers

    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1; // Assign thread number

        // Create a thread
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }

        // Wait for the thread to finish before starting the next
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}

