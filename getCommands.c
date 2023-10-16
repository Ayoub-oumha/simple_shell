#include "main.h"

/**
 * removeLeading - removeLeading characters (space tab \n)
 * @str: str
*/

void removeLeading(char *str)
{
	int i = 0, j;
	int k = 0;

	if (str != NULL)
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			i++;
		}
		for (j = i; str[j] != '\0'; j++)
		{
			str[k] = str[j];
			k++;
		}
		str[k] = '\0';
	}
}

/**
 * getLineNumbers - getLineNumbers
 * @CommandInput: user input
 * Return: number of lines
*/
size_t getLineNumbers(char *CommandInput)
{
	size_t n = 0;
	char *row_splits;
	char *dup_input = strdup(CommandInput);

	if (dup_input != NULL)
	{
		removeLeading(dup_input);
		if (dup_input != NULL && _strlen(dup_input) > 0)
		{
			row_splits = strtok(dup_input, newLineChar);
			while (row_splits != NULL)
			{
				n++;
				row_splits = strtok(NULL, newLineChar);
			}
		}
		free(dup_input);
	}
	return (n);
}

/**
 * getWordsInColumn - get number of words
 * @input: line
 * @i: number of lines
 * Return: number of words
*/
size_t getWordsInColumn(char *line, size_t i)
{
	size_t wordCount = 0, c_row;
	char *words, *d_line = strdup(line);

	if (d_line != NULL)
	{
	words = strtok(d_line, newLineChar);
	while (words != NULL && c_row < i)
	{
		words = strtok(NULL, newLineChar);
		c_row++;
	}
	if (words != NULL)
	{
		words = strtok(words, spaceChar);
		while (words != NULL)
		{
			wordCount++;
			words = strtok(NULL, spaceChar);
		}
	}
	free(d_line);
	}
	return (wordCount);
}

/**
 * getWordByIndice - getWordByIndice
 * @input: user input
 * @i: number of line
 * @j: number of word in line
 * Return: the word
*/

char *getWordByIndice(char *input, size_t i,
								size_t j)
{
	size_t c_j = 0, c_i = 0;
	char *lines, *words, *linesDup, *substring = NULL;
	char *d_line = strdup(input);

	lines = strtok(d_line, newLineChar);
	while (lines != NULL && c_i < i)
	{
		lines = strtok(NULL, newLineChar);
		c_i++;
	}
	if (lines != NULL)
	{
		linesDup = strdup(lines);
		words = strtok(linesDup, spaceChar);
		c_j = 0;
		while (words != NULL && c_j < j)
		{
			words = strtok(NULL, spaceChar);
			c_j++;
		}
		if (words != NULL)
			substring = strdup(words);
		free(linesDup);
	}
	if (d_line != NULL)
		free(d_line);
	return (substring);
}

/**
* getCommands - get matrix of input
* @commandLine: point to user input
* Return: mattrix of words in input
*/

char ***getCommands(char *commandLine)
{
	char  ***inputMatrix = NULL, *duplicateCommandLine = strdup(commandLine);
	size_t n = 0, m = 0, i = 0, j = 0;

	if (duplicateCommandLine != NULL)
	{
		n = getLineNumbers(duplicateCommandLine);
		if (n > 0)
		{
		inputMatrix = (char ***)malloc((n + 1) * sizeof(char **));
		if (inputMatrix != NULL)
		{
			for (i = 0; i < n ; i++)
			{
				m = getWordsInColumn(duplicateCommandLine, i);
				inputMatrix[i] = malloc(((m + 1) * sizeof(char *)));
				if (inputMatrix[i] != NULL)
				{
					for (j = 0; j < m; j++)
						inputMatrix[i][j] = getWordByIndice
										(duplicateCommandLine, i, j);
					inputMatrix[i][m] = NULL;
				}
				else
				{
					freeMartArgV(inputMatrix, i);
					break;
				}
			}
			if (inputMatrix != NULL)
				inputMatrix[n] = NULL;
		}
	}
	free(duplicateCommandLine);
	}
	return (inputMatrix);
}

