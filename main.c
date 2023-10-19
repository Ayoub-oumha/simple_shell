#include "main.h"

/**
* isInteractive - isInteractive
* @ac: number of agruments
* Return: true if interactive
*/
int isInteractive(int ac)
{
	if (!(!isatty(STDIN_FILENO) && ac == 1) || (!isatty(STDIN_FILENO) && ac > 1))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * putString - function prints a string
 * @s: tring to print
 */

void putString(const char *s)
{
	int x;

	for (x = 0; s[x] != '\0'; x++)
	{
		write(1, &s[x], 1);
	}
}

/**
* NonI - non interactive
* @executeName: executeName file
* @endCode: final code of program
*/

void NonI(char *executeName, int *endCode)
{
	char ***commands, *commandLine, buffer[1024];
	ssize_t len;

	len = read(STDIN_FILENO, buffer, 1023);
	if (len > 0)
	{
		commandLine = malloc(len + 1);
		if (commandLine != NULL)
		{
			buffer[len] = '\0';
			_strcpy(commandLine, buffer);
			commands = getCommands(commandLine);
			if (commands != NULL && executeName != NULL)
			{
				runCmd(executeName, commandLine, commands, endCode);
			}
			free(commandLine);
		}
	}
}

/**
* main - main function
* @ac: number of agrument
* @argv: table of agruments
* Return: error
*/
int main(int ac, char **argv)
{
	int *endCode;
	ssize_t chars_count;
	char *commandLine = NULL;
	size_t inputSize = 0;
	char *executeName = argv[0];
	char ***commands;

	endCode = malloc(sizeof(int));
	*endCode = EXIT_SUCCESS;
	if (isInteractive(ac))
	{
		while (1)
		{
			putString("#cisfun$ ");
			chars_count = getline(&commandLine, &inputSize, stdin);
			if (chars_count == EOF)
			{
				printf("Exit Shell\n");
				exit(EXIT_SUCCESS);
			}
			commands = getCommands(commandLine);
			if (commands != NULL)
				runCmd(executeName, commandLine, commands, endCode);
		}
		clearPointers(2, &commandLine, &argv);
		return (*endCode);
	}
	NonI(executeName, endCode);
	return (*endCode);
}
