#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char name[50];
    int result;
} ThreadData;

void* calculate_ascii_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->result = 0;
    for (int i = 0; data->name[i] != '\0'; i++) {
        data->result += data->name[i];
    }
    return NULL;
}

void* compare_results(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    if (data[0].result == data[1].result && data[1].result == data[2].result) {
        printf("Youreka\n");
    } else if (data[0].result == data[1].result || data[1].result == data[2].result || data[0].result == data[2].result) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadData data[3];

    for (int i = 0; i < 3; i++) {
        printf("Enter name for user %d: ", i + 1);
        scanf("%s", data[i].name);
    }

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, calculate_ascii_sum, &data[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_create(&threads[3], NULL, compare_results, data);
    pthread_join(threads[3], NULL);

    return 0;
}



