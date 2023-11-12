#include "shell.h"

/**
 * non_interactive - functions for inputs
 * @void: parameter
 *
 * Return: Null
*/

void non_interactive(void)
{
	int arg_count = 0;
	char input[MAX_INPUT_LENGTH];
	char command[MAX_INPUT_LENGTH], *args[MAX_ARGS];

	if (fgets(input, sizeof(input), stdin) != NULL)
	{
		input[strlen(input) - 1] = '\0';
		parse_command(input, command, args, &arg_count);
		execute_command(input, args);
	}

	free2DArr(args, arg_count);
}
