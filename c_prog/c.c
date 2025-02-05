#include <stdio.h>
#include <ctype.h>
#include <string.h>

void check_password(const char *password) {
    int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;
    const char *special_chars = "_$#@";

    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i])) has_lower = 1;
        else if (isupper(password[i])) has_upper = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else if (strchr(special_chars, password[i])) has_special = 1;
    }

    if (!has_lower) printf("Lowercase character missing\n");
    if (!has_upper) printf("Uppercase character missing\n");
    if (!has_digit) printf("Digit missing\n");
    if (!has_special) printf("Special character missing\n");
    if (has_lower && has_upper && has_digit && has_special) printf("OK\n");
}

int main() {
    char password[100];
    printf("Enter password: ");
    scanf("%s", password);
    check_password(password);
    return 0;
}

