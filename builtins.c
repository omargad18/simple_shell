#include "shell.h"

/**
 *  builtin_cd - function got to folder
 *  argv: parameter
 *  Return: 0 success or -1
*/

int builtin_cd(char **argv)
{
	if (argv[0] == NULL)
	{
		argv[0] = getenv("HOME");
	}

	if (chdir(argv[0]) != 0)
	{
		perror("cd");
		return (-1);
	}

	return (0);
}
/**
 *  builtin_env - function check env
 *  argv: parameter
 *  Return: -1 success
*/
int builtin_env(char **argv)
{
	int itr = 0;
	(void)(**argv);

	while (environ[itr])
	{
		write(STDOUT_FILENO, environ[itr], strlen(environ[itr]));
		write(STDOUT_FILENO, "\n", 1);
		itr++;
	}
	return (-1);
}
/**
 *  builtin_exit - function exit
 *  argv: parameter
 *  Return: 3 success
*/
int builtin_exit(char **argv)
{
	if (argv[0])
	{
		return (atoi(argv[0]));
	}
	else
	{
		return (3);
	}
}
