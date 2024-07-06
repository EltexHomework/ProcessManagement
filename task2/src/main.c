#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void fork_processes();

void print_process_info(int process_index);

int main(void) {
  fork_processes();
  return 0;
}

void fork_processes() {
  int status;
  // process 1
  if (fork() == 0) {
    print_process_info(1);
    // process 3
    if (fork() == 0) {
      print_process_info(3);
      exit(3);
    }
    // process 4
    if (fork() == 0) {
      print_process_info(4);
      exit(4);
    }

    while (wait(&status) > 0);
    exit(1);
  }
  
  // process 2
  if (fork() == 0) {
    print_process_info(2);
    // process 5
    if (fork() == 0) {
      print_process_info(5);
      exit(5);
    }

    while (wait(&status) > 0);
    exit(2);
  }

  while (wait(&status) > 0);      
}

void print_process_info(int process_index) {
  printf("Process %d\npid: %d\nppid: %d\n", process_index, getpid(), getppid());
}
