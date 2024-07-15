#include "headers/interpretor.h"

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
  char** args = (char**) malloc(ARG_LENGTH * sizeof(char*)); 

  while (1) {
    print_user_info(interpretor); 
    
    if (fgets(request, sizeof(request), stdin) == NULL) {
      perror("fgets error");
      return;
    }

    parse(request, args); 
    execute(interpretor, args);
  }
}

void execute(struct interpretor* interpretor, char** args) {
  if (strcmp(args[0], "cd") == 0) {
    change_dir(interpretor, args[1]);
    return;
  } else if (strcmp(args[0], "exit") == 0) {
    free(args);
    dispose(interpretor);
    exit(EXIT_SUCCESS);
  }

  pid_t child = fork();

  if (child < 0) {
    perror("fork error");
    exit(EXIT_FAILURE);
  } else if (child == 0) {
    if (execvp(args[0], args) < 0) {
      perror("exec error");
      exit(EXIT_FAILURE);
    }
  } else {
    int status;
    if (waitpid(child, &status, 0) == -1) {
      perror("waitpid error");
    }
  }
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

void parse(char input[INPUT_LENGTH], char** args) {
  int i = 0;
  char* token = strtok(input, " \n");
   
  while (token != NULL) {
    args[i] = token;
    token = strtok(NULL, " \n");
    i++;
  }
  args[i] = NULL;
}

void dispose(struct interpretor* interpretor) {
  free(interpretor);
}
