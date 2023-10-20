#include "main.h"

/**
 * freeTable - free table
 * @toFree: table
 */

void freeTable(char **toFree)
{
	char **a = toFree;

	if (!toFree)
		return;
	while (*toFree)
		free(*toFree++);
	free(a);
}

/**
 * clearShellVasrs - free shell variable
 * @shellVars: struct of variable of custom shell
 * @clearr: clear all if 1
 */

void clearShellVasrs(shellVarsStru *shellVars, int clearr)
{
	freeTable(shellVars->argv);
	shellVars->argv = NULL;
	shellVars->path = NULL;
	if (clearr)
	{
		if (shellVars->envLisst)
			free_listint_safe(&(shellVars->envLisst));
		if (shellVars->history)
			free_listint_safe(&(shellVars->history));
		if (!shellVars->cmdBuffe)
			free(shellVars->arg);
		if (shellVars->alias)
			free_listint_safe(&(shellVars->alias));
		freeTable(shellVars->environ);
		shellVars->environ = NULL;
		free(shellVars->cmdBuffe);
		shellVars->cmdBuffe = NULL;
		if (shellVars->filedesiptor > 2)
			close(shellVars->filedesiptor);
		_putchar(EXITT);
	}
}

/**
 * isCommand - is file a command
 * @path: path of file
 * Return: 1 ORC 0
 */
int isCommand(char *path)
{
	struct stat statCommand;

	if (!path || stat(path, &statCommand))
		return (0);
	if (statCommand.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * getPath - find command in pth
 * @pathDir: path
 * @cammand: the cammand to fin
 * Return: path of command in shell
 */

char *getPath(char *pathDir, char *cammand)
{
	char *path;
	int i = 0, c_i = 0, j = 0, k = 0;
	static char buffer[1024];

	if (!pathDir)
		return (NULL);
	if ((_strlen(cammand) > 2) && findInS(cammand, "./"))
		if (isCommand(cammand))
			return (cammand);
	while (1)
	{
		if (!pathDir[i] || pathDir[i] == ':')
		{
			for (k = 0, j = c_i; j < i; j++)
				if (pathDir[j] != ':')
					buffer[k++] = pathDir[j];
			buffer[k] = 0;
			path = buffer;
			if (!*path)
				_strcat(path, cammand);
			else
			{
				_strcat(path, "/");
				_strcat(path, cammand);
			}
			if (isCommand(path))
				return (path);
			if (!pathDir[i])
				break;
			c_i = i;
		}
		i++;
	}
	return (NULL);
}

