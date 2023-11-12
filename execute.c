#include "shell.h"

int execute_executables(char *command, char **argv)
{

    pid_t pid;
    int StatProcess;
    extern char **environ;


    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        char *cmdPath = getCmdPath(command);
        int arg_count = 0, i;
        char **new_argv = (char **)malloc((arg_count + 2) * sizeof(char *));

        if (cmdPath == NULL)
        {
            fprintf(stderr, "./hsh: %s: command not found\n", command);
            return -1;
        }

        if (access(cmdPath, X_OK) == -1)
        {
            perror(cmdPath);
            return -1;
        }

        while (argv[arg_count] != NULL)
        {
            arg_count++;
        }

        if (new_argv == NULL)
        {
            perror("malloc");
            return -1;
        }

        new_argv[0] = command;
        for (i = 0; i < arg_count; i++)
        {
            new_argv[i + 1] = argv[i];
        }

        new_argv[arg_count + 1] = NULL;

        execve(cmdPath, new_argv, environ);

        perror(cmdPath);
        return -1;
    }
    else
    {
        waitpid(pid, &StatProcess, WUNTRACED);
        return WEXITSTATUS(StatProcess);
    }
}
