#ifndef INTERPRETOR_H
#define INTERPRETOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_LENGTH 128
#define INPUT_LENGTH 256
#define FILENAME_LENGTH 128
#define ARG_LENGTH 64

struct interpretor {
  char* username;  
  char current_dir[PATH_LENGTH];
};

struct interpretor* create_interpretor();

void run_interpretor(struct interpretor* interpretor);

void execute(struct interpretor* interpretor, char** args);

void change_dir(struct interpretor* interpretor, char* path);

void print_user_info(struct interpretor* interpretor);

void parse(char input[INPUT_LENGTH], char** args);

void dispose(struct interpretor* interpretor);

#endif /* INTERPRETOR_H */
