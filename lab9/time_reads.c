/* The purpose of this program is to practice writing signal handling
 * functions and observing the behaviour of signals.
 */

#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>



/* Message to print in the signal handling function. */
#define MESSAGE "%ld reads were done in %ld seconds.\n"

/* Global variables to store number of read operations and seconds elapsed. */
long num_reads, seconds;

void handler(int code) {
    // Signal handler function: prints the number of reads and the elapsed time.
    printf(MESSAGE, num_reads, seconds);
    exit(0);
}

int main(int argc, char **argv) {
    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: time_reads s filename\n");
        exit(1);
    }

    // Convert first argument to long for seconds
    seconds = strtol(argv[1], NULL, 10);

    // Open the file
    FILE *fp;
    if ((fp = fopen(argv[2], "rb")) == NULL) {
        perror("fopen");
        exit(1);
    }
    // Seed the random number generator with the current time  
    srandom(time(NULL));  

    // Set up a signal handler structure for the SIGPROF signal
    struct sigaction new_sig = {0};   
    new_sig.sa_handler = handler;   
    sigaction(SIGPROF, &new_sig, NULL);    

    // Configure a timer that sends SIGPROF when it expires
    struct itimerval new_time = {0};  
    new_time.it_value.tv_sec = seconds;   // Set the timer for 'seconds' seconds
    if (setitimer(ITIMER_PROF, &new_time, NULL) < 0) {  
    perror("setitimer");   // If setting the timer fails, print an error message
    exit(1);               // Exit the program with an error status
    }  

    // Initialize a counter for the number of reads
    num_reads = 0;  
    int num, output;   

    // Infinite loop to read random integers from a file
    for (;;) {  
    num = random() % 100;                // Generate a random number between 0 and 99
    fseek(fp, sizeof(int) * num, SEEK_SET); // Move the file pointer to the position of the random integer
    if (fread(&output, sizeof(int), 1, fp) < 1) {  
        perror("fread");                 // If reading fails, print an error message
        exit(1);                         // Exit the program with an error status
    }  
    fprintf(stderr, "Count %ld: %d\n", num_reads, output);  // Print the read integer to stderr
    num_reads++;                        // Increment the read counter      
    }  

    fclose(fp); // Close the file (Note: This line is unreachable due to the infinite loop)
    return 0;   // Return from the function (Note: This is also unreachable)
   
}


// Optional Explorations: 
// - Uncomment and modify sections below to explore different behaviors.
//   These sections are for experimental purposes and not required for the main functionality.

/*
// Optional: Writing random values instead of reading.
int random_value = random();
fseek(fp, sizeof(int) * num, SEEK_SET);
if (fwrite(&random_value, sizeof(int), 1, fp) < 1) {
    perror("fwrite");
    exit(1);
}
*/

/*
// Optional: Mask SIGPROF during printing.
sigset_t mask, oldmask;
sigemptyset(&mask);
sigaddset(&mask, SIGPROF);
sigprocmask(SIG_BLOCK, &mask, &oldmask); // Block SIGPROF.
fprintf(stderr, "Count %ld: %d\n", num_reads, output);
sigprocmask(SIG_SETMASK, &oldmask, NULL); // Unblock SIGPROF.
*/
