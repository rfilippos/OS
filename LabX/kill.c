#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Child received signal from parent.\n");
        exit(0);  // Child process exits after handling the signal
    }
}

int main() {
    pid_t pid;
    pid = fork();
    
    if (pid == -1) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        signal(SIGUSR1, signal_handler);  // Set signal handler
        pause();  // Wait for signal
    } else {
        // Parent process
        sleep(1);  // Ensure child is ready to receive signal
        kill(pid, SIGUSR1);  // Send signal to child
        printf("Parent sent signal to child.\n");
        wait(NULL);  // Wait for child to finish
    }

    return 0;
}

