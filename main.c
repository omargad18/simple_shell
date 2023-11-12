#include "shell.h"

/**
 * main - shell returners
 *
 * Return: 0
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 0)
	{
		non_interactive();
	}
	else
	{
		interactive();
	}
	return (0);

}
