#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n); // Read the size of the array

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]); // Read each number
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d is even\n", arr[i]);
        } else {
            printf("%d is odd\n", arr[i]);
        }
    }

    return 0;
}

