#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    // Validate command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: childcreates <iterations>\n");
        exit(EXIT_FAILURE);
    }

    // Convert the command line argument to an integer
    int iterations = atoi(argv[1]);
    if (iterations < 0) {
        fprintf(stderr, "Error: Number of iterations cannot be negative.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize loop iterator and child process status variable
    int i;
    int child_status;

    // Iterate and create child processes in a chain
    for (i = 0; i < iterations; ++i) {
        // Create a child process
        pid_t pid = fork();

        // Handle fork failure
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid > 0) {
            // In parent process
            // Wait for child process to finish
            waitpid(pid, &child_status, 0);
            break; // Parent does not create more children
        }
        // If pid == 0, we are in the child process, and the loop will continue
    }

    // Print process information
    printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);

    return EXIT_SUCCESS;
}
