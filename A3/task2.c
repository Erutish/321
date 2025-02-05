#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Message structure
struct msg {
    long int type;
    char txt[6];
};

int main() {
    key_t key;
    int msgid;
    struct msg message;

   
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Please enter the workspace name:\n");
    char workspace[10];
    scanf("%s", workspace);

    // Log in process
    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(msgid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    } else {
        printf("Workspace name sent to otp generator from log in: %s\n", workspace);
        message.type = 1; 
        strncpy(message.txt, workspace, 6);
        msgsnd(msgid, &message, sizeof(message.txt), 0);
    }

    pid_t pid = fork();

    if (pid == 0) {
        
        msgrcv(msgid, &message, sizeof(message.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n", message.txt);

       
        int otp = getpid();
        snprintf(message.txt, 6, "%d", otp);

        message.type = 2; 
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to log in from OTP generator: %s\n", message.txt);

        message.type = 3; 
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", message.txt);

        pid_t mail_pid = fork();

        if (mail_pid == 0) {
           
            msgrcv(msgid, &message, sizeof(message.txt), 3, 0);
            printf("Mail received OTP from OTP generator: %s\n", message.txt);

            message.type = 4; 
            msgsnd(msgid, &message, sizeof(message.txt), 0);
            printf("OTP sent to log in from mail: %s\n", message.txt);

            exit(0); 
        } else {
            wait(NULL); 
            exit(0); 
        }
    } else {
        wait(NULL); 

        // Log in continues
        msgrcv(msgid, &message, sizeof(message.txt), 2, 0);
        printf("Log in received OTP from OTP generator: %s\n", message.txt);
        char otp_from_otp[6];
        strncpy(otp_from_otp, message.txt, 6);

        msgrcv(msgid, &message, sizeof(message.txt), 4, 0);
        printf("Log in received OTP from mail: %s\n", message.txt);
        char otp_from_mail[6];
        strncpy(otp_from_mail, message.txt, 6);

        // Compare OTPs
        if (strcmp(otp_from_otp, otp_from_mail) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        // Remove the message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}

