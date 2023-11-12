#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

/**
 * promptDirectory - print "$ "
 *
 * Return: NULL
 */
void promptDirectory(void)
{
	printf("($) ");
}

/**
 * parse_command - Start Token
 * @input: parameter for length input
 * @command: command the new input
 * @args: parameter
 * @arg_count: parameter for counter
 *
 * Return: NULL
 */
void parse_command(char *input, char *command, char **args, int *arg_count)
{
	char *token;

	token = strtok(input, " ");
	if (token != NULL)
	{
		strcpy(command, token);
		token = strtok(NULL, " ");
		*arg_count = 0;
		while (token != NULL)
		{
			args[*arg_count] = (char *)malloc(strlen(token) + 1);
			strcpy(args[*arg_count], token);
			(*arg_count)++;
			token = strtok(NULL, " ");
		}
		args[*arg_count] = NULL;
	}
}

/**
 * free2DArr - execute the function
 * @args: parameter for argument
 * @arg_count: parameter for define counter
 *
 * Return: Null
 */
void free2DArr(char **args, int arg_count)
{
	int i;

	for (i = 0; i < arg_count; i++)
	{
		free(args[i]);
	}
}

/**
 * *getCmdPath - command length and directory Length
 * @Comand: counter the path
 *
 * Return: return Null
 */
char *getCmdPath(char *Comand)
{
	char *Path, *CpyPath, *Token, *FilePath;
	int ComLength, DirectoryLength;
	struct stat buffer;

	Path = getenv("PATH");
	if (Path)
	{
		CpyPath = strdup(Path);
		ComLength = strlen(Comand);
		Token = strtok(CpyPath, ":");
		while (Token != NULL)
		{
			DirectoryLength = strlen(Token);
			FilePath = malloc(ComLength + DirectoryLength + 2);
			strcpy(FilePath, Token);
			strcat(FilePath, "/");
			strcat(FilePath, Comand);
			strcat(FilePath, "\0");
			if (stat(FilePath, &buffer) == 0)
			{
				free(CpyPath);
				return (FilePath);
			}
			else
			{
				free(FilePath);
				Token = strtok(NULL, ":");
			}
		}
		free(CpyPath);
		if (stat(Comand, &buffer) == 0)
		{
			return (Comand);
		}
		return (NULL);
	}
	return (NULL);
}

/**
 * execute_command - command the state Process
 * @comand: parameter for count
 * @argv: parameter for ad state
 *
 * Return: return 0
 */


int execute_command(char *command, char **argv)
{

     struct builtins builtInCommands[] = {
        {"exit", &builtin_exit},
        {"env", &builtin_env},
        {"cd", &builtin_cd}
    };

	int itr;

	if (command == NULL)
		return (-1);

	for (itr = 0; itr < 3; itr++)
	{
		if (strcmp(command, builtInCommands[itr].command) == 0)
		{
			return ((*builtInCommands[itr].function)(argv));
		}
	}
	return (execute_executables(command, argv));
}
