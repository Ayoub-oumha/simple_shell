#include "main.h"

/**
 * handlErrorFile - handle error file
 * @argvM: table of agrument
 */

void handlErrorFile(char **argvM)
{
	if (errno == EACCES)
		exit(126);
	else if (errno == ENOENT)
	{
		printError(argvM[0]);
		printError(": 0: Can't open ");
		printError(argvM[1]);
		printErrorChar('\n');
		printErrorChar(EXITT);
		exit(127);
	}

}


/**
 * HlistBuild - add line to hist
 * @buffer: buffer
 * @linecount: line number of history
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int HlistBuild(char *buffer, int linecount, shellVarsStru *shellVars)
{
	list_t *histNode = shellVars->history ? shellVars->history : NULL;

	add_node_end(&histNode, buffer, linecount);
	if (!shellVars->history)
		shellVars->history = histNode;
	return (0);
}

/**
 * Hreadd - second part of hread
 * @shellVars: struct of variable of custom shell
 * Return: history number of lines
 */

int Hreadd(shellVarsStru *shellVars)
{
	list_t *head = shellVars->history;
	int i = 0;

	while (shellVars->historyNLines-- >= 4096)
		delete_nodeint_at_index(&(shellVars->history), 0);
	while (head)
	{
		head->num = i;
		head = head->next;
		i++;
	}
	return (shellVars->historyNLines = i);
}

/**
 * Hread - read hist from file
 * @shellVars: struct of variable of custom shell
 * Return: nubmer hostiry ORC 0
 */

int Hread(shellVarsStru *shellVars)
{
	struct stat fileState;
	int i, endLine = 0, counter = 0;
	ssize_t fileSize = 0, fileDisiptor, fileContent;
	char *executableName, *buffer = NULL;

	executableName = getShellH(shellVars);
	if (!executableName)
		return (0);
	fileDisiptor = open(executableName, O_RDONLY);
	free(executableName);
	if (fileDisiptor == -1)
		return (0);
	if (!fstat(fileDisiptor, &fileState))
		fileSize = fileState.st_size;
	if (fileSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);
	fileContent = read(fileDisiptor, buffer, fileSize);
	close(fileDisiptor);
	buffer[fileSize] = 0;
	if (fileContent <= 0)
		return (free(buffer), 0);
	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			HlistBuild(buffer + endLine, counter++, shellVars);
			endLine = i + 1;
		}
	if (endLine != i)
		HlistBuild(buffer + endLine, counter++, shellVars);
	free(buffer);
	shellVars->historyNLines = counter;
	Hreadd(shellVars);
	return (shellVars->historyNLines);
}

/**
 * main - start of the code
 * @ac: number of agruments
 * @argvM: table of agrument
 * Return: exit code
 */

int main(int ac, char **argvM)
{
	shellVarsStru shellVars[] = { INIT_VARS_SHELL };
	int fileDispitor = 2;
	list_t *envLisst = NULL;
	size_t i;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDispitor)
		: "r" (fileDispitor));
	if (ac == 2)
	{
		fileDispitor = open(argvM[1], O_RDONLY);
		if (fileDispitor == -1)
		{
			handlErrorFile(argvM);
			return (EXIT_FAILURE);
		}
		shellVars->filedesiptor = fileDispitor;
	}
	for (i = 0; environ[i]; i++)
		add_node_end(&envLisst, environ[i], 0);
	shellVars->envLisst = envLisst;
	Hread(shellVars);
	executeCMD(argvM, shellVars);
	return (EXIT_SUCCESS);
}

