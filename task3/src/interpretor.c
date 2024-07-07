#include "headers/interpretor.h"
#include <stdio.h>

struct interpretor* create_interpretor() {
  struct interpretor* interpretor = (struct interpretor*) 
    malloc(sizeof(struct interpretor));
  
  if (!interpretor) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  
  interpretor->username = getlogin();
  if (interpretor->username == NULL) {
    perror("getlogin error");
    exit(EXIT_FAILURE);
  }

  if (getcwd(interpretor->current_dir, sizeof(interpretor->current_dir)) == NULL) {
    perror("getcwd error");
    exit(EXIT_FAILURE);
  }

  return interpretor;
}

void run_interpretor(struct interpretor* interpretor) {
  char request[INPUT_LENGTH];

  while (1) {
    print_user_info(interpretor); 
    
    if (fgets(request, sizeof(request), stdin) == NULL) {
      perror("fgets error");
      return;
    }
    
    execute(interpretor, request);
  }
}

void execute(struct interpretor* interpretor, char* request) {
  pid_t child = fork();
  int status;
  char* saveptr;

  if (child == 0) {
    char* program_name = strtok_r(request, " \n", &saveptr);
   
    if (strcmp(program_name, "cd") == 0) {
      char* path = strtok_r(NULL, " \n", &saveptr);   
      change_dir(interpretor, path); 
      exit(EXIT_SUCCESS); 
    } else if (strcmp(program_name, "exit") == 0) {
      exit(EXIT_SUCCESS); 
    } else {
      system(request);
      exit(EXIT_SUCCESS); 
    }
  }

  while ((child = wait(&status)) > 0);
}

void print_user_info(struct interpretor* interpretor) {
  printf("%s:%s$ ", interpretor->username, interpretor->current_dir);
}

void change_dir(struct interpretor* interpretor, char* path) {
  if (chdir(path) != 0) {
    perror("chdir error");      
  }

  if (getcwd(interpretor->current_dir, sizeof(interpretor->current_dir)) == NULL) {
    perror("getcwd error");
  }
}
