#include <stdio.h>
#include <string.h>

void check_email(const char *email) {
    if (strstr(email, "@kaaj.com")) {
        printf("Email address is outdated\n");
    } else if (strstr(email, "@sheba.xyz")) {
        printf("Email address is okay\n");
    } else {
        printf("Invalid email domain\n");
    }
}

int main() {
    char email[100];
    printf("Enter email: ");
    scanf("%s", email);
    check_email(email);
    return 0;
}

