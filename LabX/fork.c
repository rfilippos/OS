#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Fork 3 times
    for (int i = 0; i < 3; i++) {
        pid = fork();
        
        if (pid == -1) {
            // Error in fork
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("Child process PID: %d\n", getpid());
            break;  // Child exits the loop
        }
    }

    // Parent prints its PID
    if (pid != 0) {
        printf("Parent process PID: %d\n", getpid());
    }

    return 0;
}

