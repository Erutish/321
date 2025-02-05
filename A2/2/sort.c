#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Descending order
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n); // Read the size of the array

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]); // Read each number
    }

    qsort(arr, n, sizeof(int), compare); // Sort in descending order

    printf("Sorted array in descending order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}


