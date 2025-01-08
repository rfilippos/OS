#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[100];

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    
    if (pid == -1) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process reads from the pipe
        close(pipe_fd[1]);  // Close write end
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);
        close(pipe_fd[0]);
    } else {
        // Parent process writes to the pipe
        close(pipe_fd[0]);  // Close read end
        write(pipe_fd[1], message, sizeof(message));
        close(pipe_fd[1]);
        wait(NULL);  // Wait for child to finish
    }

    return 0;
}

