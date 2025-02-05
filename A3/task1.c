#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid;
    struct shared *shm;
    int pipefd[2];
    pid_t pid;


    shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shm = (struct shared *)shmat(shmid, NULL, 0);
    if (shm == (struct shared *)-1) {
        perror("shmat");
        exit(1);
    }

  
    shm->b = 1000;

    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    scanf("%s", shm->sel);
    printf("Your selection: %s\n", shm->sel);

 
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  
        close(pipefd[0]);  

        if (strcmp(shm->sel, "a") == 0) {
            int add_amount;
            printf("Enter amount to be added:\n");
            scanf("%d", &add_amount);
            if (add_amount > 0) {
                shm->b += add_amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition:\n%d\n", shm->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "w") == 0) {
            int withdraw_amount;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &withdraw_amount);
            if (withdraw_amount > 0 && withdraw_amount <= shm->b) {
                shm->b -= withdraw_amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal:\n%d\n", shm->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "c") == 0) {
            printf("Your current balance is:\n%d\n", shm->b);
        } else {
            printf("Invalid selection\n");
        }

        const char *msg = "Thank you for using";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);  
        exit(0);
    } else {  
        close(pipefd[1]);  

        wait(NULL);  

        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);

        close(pipefd[0]);  

        
        shmdt((void *)shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

