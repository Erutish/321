#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int *process_count;

void check_and_create_child() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        (*process_count)++;
        //printf("Child process created with PID: %d\n", getpid());

        if (getpid() % 2 != 0) {
            //printf("PID %d is odd, creating another child.\n", getpid());
            check_and_create_child();
        }

        exit(0);
    } else {
        wait(NULL);
    }
}

int main() {
    process_count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (process_count == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    *process_count = 1;

    pid_t a = fork();
    if (a == 0) {
        (*process_count)++;
        check_and_create_child();
        exit(0);
    }

    pid_t b = fork();
    if (b == 0) {
        (*process_count)++;
        check_and_create_child();
        exit(0);
    }

    pid_t c = fork();
    if (c == 0) {
        (*process_count)++;
        check_and_create_child();
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Total number of processes created: %d\n", *process_count);

    munmap(process_count, sizeof(int));

    return 0;
}
