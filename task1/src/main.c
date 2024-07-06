#include <stdio.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();

  if (pid < 0) {
    printf("Error creating process");
  }
  // Child
  else if (pid == 0) {
    pid_t child_pid = getpid();
    printf("Child pid: %d\n", child_pid);
  } 
  // Parent
  else {
    pid_t parent_pid = getpid();
    printf("Parent pid: %d\n", parent_pid);
  }
  return 0;
}

