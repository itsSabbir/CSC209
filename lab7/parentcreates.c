#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        // If not, print an error message and exit with a failure status
        fprintf(stderr, "Usage: parentcreates <num_children>\n");
        exit(EXIT_FAILURE);
    }

    // Convert the command line argument from a string to an integer
    // This integer represents the number of child processes to create
    int num_children = atoi(argv[1]);
    
    // Ensure that the number of children specified is not negative
    if (num_children < 0) {
        fprintf(stderr, "Error: Number of children cannot be negative.\n");
        exit(EXIT_FAILURE);
    }

    // Iterate from 0 to num_children - 1
    // Each iteration represents an attempt to create a new child process
    for (int i = 0; i < num_children; ++i) {
        // Create a child process
        pid_t child_pid = fork();

        // Check if the fork operation failed
        if (child_pid < 0) {
            // If it did, print an error message and exit with a failure status
            perror("Failed to create child");
            exit(EXIT_FAILURE);
        } 
        else if (child_pid > 0) {
            // If we are in the parent process (fork returns child's PID)
            // Wait for the child process to finish execution
            int child_status;
            waitpid(child_pid, &child_status, 0);

            // Print information about the parent process and the child process
            printf("Parent PID: %d, Child PID: %d, Index: %d\n", getppid(), getpid(), i);

            // Break out of the loop to prevent the parent from creating more children
            break;
        }
        // If child_pid == 0, we are in the child process, and the loop will continue
        // This allows for the creation of a chain of child processes
    }

    // Handle the special case where no children are specified
    if (num_children == 0) {
        // In this case, simply print the process's own information
        printf("Parent PID: %d, PID: %d\n", getppid(), getpid());
    }

    // Exit the program successfully
    return EXIT_SUCCESS;
}
