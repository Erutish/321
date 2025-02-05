#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int main() {
    int n;
    int status;
    printf("Enter the number of elements: ");
    scanf("%d", &n); // Read the size of the array

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]); // Read each number
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process Sort 
        qsort(arr, n, sizeof(int), compare);
        printf("Child process: Sorted array in descending order: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        exit(0);
    } else {
        // Parent process 
        wait(&status);

        printf("Parent process: Odd/Even status of the numbers:\n");
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                printf("%d is even\n", arr[i]);
            } else {
                printf("%d is odd\n", arr[i]);
            }
        }
    }

    return 0;
}

