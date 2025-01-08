#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

// write parent and child process PIDs to pids.txt

int main() {
    pid_t pid;
    int fd = open("pids.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("File open failed");
        return 1;
    }

    pid = fork();
    
    if (pid == -1) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child writes PID to file
        dprintf(fd, "Child PID: %d\n", getpid());
    } else {
        // Parent writes PID to file
        dprintf(fd, "Parent PID: %d\n", getpid());
        wait(NULL);  // Wait for child to finish
    }

    close(fd);
    return 0;
}

