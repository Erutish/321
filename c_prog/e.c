#include <stdio.h>
#include <string.h>

void check_palindrome() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    int length = strlen(str);
    int is_palindrome = 1; // Assume it is a palindrome unless proven otherwise

    // Compare characters from start and end using a for loop
    for (int i = 0; i < length / 2; i++) {
        if (str[i] != str[length - 1 - i]) {
            is_palindrome = 0; // Not a palindrome
            break; // Exit the loop if characters don't match
        }
    }

    if (is_palindrome) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }
}

int main() {
    check_palindrome();
    return 0;
}


