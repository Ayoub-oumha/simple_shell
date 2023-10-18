#include "main.h"

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
* main - main
* @ac: d
* @argv: f
* Return: int
*/
int main(int ac, char **argv)
{
	int *endCode;
	ssize_t chars_count;
	char *commandLine = NULL;
	size_t inputSize = 0;
	char *executeName = argv[0];
	char ***commands;

	(void) ac;
	endCode = malloc(sizeof(int));
	*endCode = EXIT_SUCCESS;
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
