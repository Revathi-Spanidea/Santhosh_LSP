/*4.Develop a program that launches multiple child processes using the fork system call. Each child process should execute a different command specified by the parent process, and the parent process should wait for all child processes to complete before exiting.*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Array to store child process IDs
    pid_t child_pids[3];
    
    // Command strings for child processes
    const char *commands[][4] = {
        {"ls", NULL},
        {"date", NULL},
        {"echo", "Hello,", "World!", NULL}
    };
    
    // Launch child processes
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process executes the command
            printf("Child %d executing command: %s\n", i+1, commands[i][0]);
            execvp(commands[i][0], (char * const *)commands[i]);
            // execvp() only returns if an error occurs
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process stores child process ID
            child_pids[i] = pid;
        }
    }
    
    // Parent process waits for all child processes to complete
    int status;
    for (int i = 0; i < 3; i++) {
        waitpid(child_pids[i], &status, 0);
        printf("Child %d exited with status %d\n", i+1, WEXITSTATUS(status));
    }
    
    printf("All child processes have completed.\n");
    
    return 0;
}

