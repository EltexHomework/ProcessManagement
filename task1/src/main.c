#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
  pid_t pid = fork();

  if (pid < 0) {
    printf("Error creating process");
  }
  // Child
  else if (pid == 0) {
    printf("___Child process___\nParent pid: %d\nProcess pid: %d\n", getppid(), getpid());
    exit(EXIT_SUCCESS);
  } 
  // Parent
  else {
    pid_t wait_pid;
    int status;
    
    // Wait for child termination. Parent process can terminate faster than child
    while ((wait_pid = wait(&status)) > 0);
    printf("___Parent process___\nParent pid: %d\nProcess pid: %d\n", getppid(), getpid());
  }
  return 0;
}

