#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    // child process
    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) {
        // Inside child process
        // grandchild process
        pid2 = fork();

        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid2 == 0) {
            // grandchild process
            printf("I am grandchild\n");
        } else {
            // Wait for grandchild to finish
            wait(&status);
            printf("I am child\n");
        }
    } else {
        // Wait for child to finish
        wait(&status);
        printf("I am parent\n");
    }

    return 0;
}

