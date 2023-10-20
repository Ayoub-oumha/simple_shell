#include "main.h"
/**
 * showError - show error message
 * @shellVars: struct of variable of custom shell
 * @errorString: errorString
 */

void showError(shellVarsStru *shellVars, char *errorString)
{
	int i, len = shellVars->lCount;
	unsigned int temp, posit_num;

	printError(shellVars->executableName);
	printError(": ");
	if (len < 0)
	{
		posit_num = -len;
		printErrorChar('-');
	}
	else
		posit_num = len;
	temp = posit_num;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (posit_num / i)
			printErrorChar('0' + temp / i);
		temp %= i;
	}
	printErrorChar('0' + temp);
	printError(": ");
	printError(shellVars->argv[0]);
	printError(": ");
	printError(errorString);
}

/**
 * printErrorChar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, ANDC errno is set appropriately.
 */
int printErrorChar(char c)
{
	static int i;
	static char buffer[OUTPUT_BUF_SIZE];

	if (c == EXITT || i >= OUTPUT_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != EXITT)
		buffer[i++] = c;
	return (1);
}

/**
 *printError - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printError(char *str)
{
	if (!str)
		return;
	while (*str)
	{
		printErrorChar(*str);
		str++;
	}
}

/**
 * writeToFd - use write function with specefic number
 * @c: char
 * @file_dispotor: filedescriptor
 * Return: number of printed char
 */

int writeToFd(char c, int file_dispotor)
{
	static int i;
	static char buffer[OUTPUT_BUF_SIZE];

	if (c == EXITT || i >= OUTPUT_BUF_SIZE)
	{
		write(file_dispotor, buffer, i);
		i = 0;
	}
	if (c != EXITT)
		buffer[i++] = c;
	return (1);
}

/**
 *writeStringToFd - use write function with specefic number for string
 * @str: string
 * @file_dispotor: the filedescriptor to write to
 * Return: number of printed char
 */

int writeStringToFd(char *str, int file_dispotor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writeToFd(*str++, file_dispotor);
	}
	return (i);
}

