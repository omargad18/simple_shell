#include "shell.h"

/**
 * interactive - functions for acrive
 * @void: parameter
 *
 * Return: 0
 */
void interactive(void)
{
	int arg_count = 0, i;
	char input[MAX_INPUT_LENGTH];
	char command[MAX_INPUT_LENGTH], *args[MAX_ARGS];
	int result = -11111;
	while (1)
	{
		memset(input, 0, sizeof(input));
		memset(command, 0, sizeof(command));
		for (i = 0; i < MAX_ARGS; i++)
		{
			args[i] = NULL;
		}
		arg_count = 0;

		promptDirectory();
		if (fgets(input, sizeof(input), stdin) != NULL)
		{
			input[strlen(input) - 1] = '\0';
			parse_command(input, command, args, &arg_count);
			if (command[0] != '\0')
			{
				result = execute_command(command, args);
			}
			free2DArr(args, arg_count);
			if (result == 3)
			{

				exit(result);
			}
		}
		else
		{
			printf("\n");
			break;
		}
	}
}

