#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

main() {
    pid_t child = fork();

    if (child == (pid_t)-1) {
        perror("Unable to create child process.\n");
        return -1;
    }
    else if (child == (pid_t)0) {
        printf("Attempting to run cat from child process...\n");
        execlp("cat", "cat", "file.txt", NULL);
        perror("Unable to run cat from child process");
        return -1;
    }
    else {
        pid_t status = 9999; // we can safely do this, as exit codes are limited to range 0-255 only.
        while (status == 9999) {
            waitpid(child, &status, 0);
        }
        printf("Child process finished with exit status %d.\n", WEXITSTATUS(status));
    }

    return 0;
}