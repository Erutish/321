#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd;
    char buffer[256];

   
    fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    printf("File '%s' opened successfully. Enter strings to write to the file.\n", argv[1]);
    printf("Enter '-1' to stop.\n");

    while (1) {
        printf("Enter a string: ");
        fgets(buffer, sizeof(buffer), stdin);

       
        buffer[strcspn(buffer, "\n")] = 0;

      
        if (strcmp(buffer, "-1") == 0) {
            break;
        }

        
        if (write(fd, buffer, strlen(buffer)) < 0) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }

       
        write(fd, "\n", 1);
    }

    printf("Finished writing to the file.\n");

   
    close(fd);
    return 0;
}

