#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

void process_function(char* name, int priority) {
    int i;
    for (i = 0; i < 5; i++) {
        printf("Process %s with priority %d is executing (%d/5)\n", name, priority, i+1);
        sleep(1);
    }
}

int main() {
    pid_t pid;
    int i;

    // Create child processes with different priorities
    for (i = 1; i <= 3; i++) {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            switch (i) {
                case 1:
                    nice(5);  // Lower priority
                    process_function("P1", 5);
                    break;
                case 2:
                    nice(0);  // Medium priority
                    process_function("P2", 0);
                    break;
                case 3:
                    nice(-5); // Higher priority
                    process_function("P3", -5);
                    break;
            }
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to finish
    for (i = 1; i <= 3; i++) {
        wait(NULL);
    }

    return 0;
}
