#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  // declares an array to store the user ID
  char user_id[MAXLINE];

  // declares an array to store the password
  char password[MAXLINE];

  /* The user will type in a user name on one line followed by a password 
     on the next.
     DO NOT add any prompts.  The only output of this program will be one 
     of the messages defined above.
     Please read the comments in validate carefully
   */

  // reads the user ID from stdin
  if(fgets(user_id, MAXLINE, stdin) == NULL) {

    // prints an error message if the read fails
    perror("fgets");
    // exits with an error code
    exit(1);
  }

  // reads the password from stdin
  if(fgets(password, MAXLINE, stdin) == NULL) {

    // prints an error message if the read fails
    perror("fgets");
    // exits with an error code
    exit(1);
  }

  // if the password ends with a newline character, remove it
  if (password[strlen(password)-1] == '\n') {
    password[strlen(password)-1] = '\0';
  }
  
  // declares an array to store the file descriptors for the pipe
  int fd[2];
  if (pipe(fd) < 0) { // creates a pipe
    perror("pipe"); // prints an error message if the pipe creation fails
    exit(1); //exits with an error code
  }

  // forks a child process
  pid_t pid = fork();
  if (pid == -1) { // checks if the fork failed
    perror("fork"); // prints an error message if the fork fails
    exit(1);
  }

  // prints an error message if the fork fails
  if (pid > 0) {

    // closes the read end of the pipe
    if (close(fd[0]) == -1) {
      perror("close"); // closes the read end of the pipe
      exit(1);
    }

    // writes the user ID to the pipe
    if (write(fd[1], user_id, strlen(user_id)) == -1) {
      perror("write"); // prints an error message if the write fails
      exit(1);
    }

    // writes the password to the pipe
    if (write(fd[1], password, strlen(password)) == -1) {
      perror("write"); // prints an error message if the write fails
      exit(1);
    }

    // close the write pipe
    if (close(fd[1]) == -1) { // close the write pipe
      perror("close");
      exit(1);
    }

  } 
  
  else {
    // closes the write end of the pipe
    if (close(fd[1]) == -1) {
      perror("close"); // prints an error message if the close fails
      exit(1);
    }

    // redirects the child process's stdin to come from the pipe
    if (dup2(fd[0], STDIN_FILENO) == -1) {
      perror("dup2"); // prints an error message if the dup2 fails
      exit(1);
    }

   


    // closes the read end of the pipe
    if (close(fd[0]) == -1) {
      perror("close"); // prints an error message if the close fails
      exit(1);
    }

    // executes the validate program
    execl("./validate", "validate", NULL);

    // prints an error message if the execl fails
    perror("execl");
    exit(1);
  }

  int status;

  // waits for the child process to finish
  wait(&status);

  // checks if the child process exited normally
  if (WIFEXITED(status)) {
    int exit_code = WEXITSTATUS(status); // stores the exit code of the child process
    switch(exit_code) { // checks the exit code

      case 0: // if the exit code is 0
        printf(SUCCESS); // prints the success message
        break;

      case 1:
        printf("Error: 'Password verified' not found in output\n");
        break;

      case 2: // if the exit code is 2
        printf(INVALID); // prints the invalid password message
        break;

      case 3: // if the exit code is 3
        printf(NO_USER); // prints the no user message
        break;
    }
  }
  
  // prints the no user message
  return 0;
}
