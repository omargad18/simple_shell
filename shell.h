#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10
#define EFO 42

struct builtins
{
    char *command;
    int (*function)(char **);
};

extern char **environ;
void promptDirectory(void);
void parse_command(char *input, char *command, char **args, int *arg_count);
void free2DArr(char **args, int arg_count);
char *getCmdPath(char *Comand);
int execute_command(char *command, char **argv);
void interactive(void);
void non_interactive(void);
int execute_executables(char *command, char **argv);
int builtin_env(char **argv);
int builtin_cd(char **argv);
int builtin_exit(char **argv);
#endif
