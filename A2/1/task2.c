#include <stdio.h>



void findPerfectNumbers(int start, int end) {
    for (int i = start; i <= end; i++) {
        int sum=0;
        for (int j=1; j<i; j++){
            if(i%j==0){
        	sum+=j;
            }
        }
        if (sum==i) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start, end;

    // Input range
    printf("Enter start of range: ");
    scanf("%d", &start);
    printf("Enter end of range: ");
    scanf("%d", &end);

    // Print perfect numbers
    findPerfectNumbers(start, end);

    return 0;
}

