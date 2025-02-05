#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {	
    int status;
    pid_t parent_pid = getpid(); // parent process ID
    printf("1. Parent process ID: %d\n", parent_pid);

    // Create child 
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed for child process");
        exit(1);
    }

    if (child_pid == 0) {
        // child process
        printf("2. Child process ID: %d\n", getpid());

        // three grandchild 
        for (int i = 0; i < 3; i++) {
            pid_t grandchild_pid = fork();

            if (grandchild_pid < 0) {
                perror("Fork failed for grandchild process");
                exit(1);
            }

            if (grandchild_pid == 0) {
                // grandchild process
                printf("3. Grandchild process ID: %d\n", getpid());
                exit(0); 
            }
        }

        // Wait for all grandchildren to finish
        for (int i = 0; i < 3; i++) {
            wait(&status);
        }

        exit(0); // Child process exits 
    }

    // parent process wait 
    wait(&status);

    return 0;
}

