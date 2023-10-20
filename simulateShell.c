#include "main.h"

/**
 * InitilizeShellVars - initializes shellVars
 * @shellVars: struct of variable of custom shell
 * @argvM: argument table
 */

void InitilizeShellVars(char **argvM, shellVarsStru *shellVars)
{
	int i, len = 0;
	list_t *node;
	char *currentPos;

	shellVars->executableName = argvM[0];
	if (shellVars->arg)
	{
		shellVars->argv = strokCustom(shellVars->arg, " \t");
		if (!shellVars->argv)
		{
			shellVars->argv = malloc(sizeof(char *) * 2);
			if (shellVars->argv)
			{
				shellVars->argv[1] = NULL;
				shellVars->argv[0] = _strdup(shellVars->arg);
			}
		}
		for (; shellVars->argv && shellVars->argv[len]; len++)
			;
		shellVars->lenAgrument = len;
		for (i = 0; i < 10; i++)
		{
			node = getNodeSta(shellVars->alias, shellVars->argv[0], '=');
			if (!node)
				break;
			currentPos = searchFirstOcc(node->str, '=');
			free(shellVars->argv[0]);
			if (!currentPos)
				break;
			currentPos = _strdup(currentPos + 1);
			if (!currentPos)
				break;
			shellVars->argv[0] = currentPos;
		}
		setAliasVar(shellVars);
	}
}

/**
 * executeCMD - smd similate
 * @shellVars: struct of variable of custom shell
 * @argvM: argument table
 * Return: 0 if success
 */

int executeCMD(char **argvM, shellVarsStru *shellVars)
{
	int builtin_ret = 0;
	ssize_t r = 0;

	while (builtin_ret != -2 && r != -1)
	{
		shellVars->lenAgrument = 0;
		shellVars->argv = NULL;
		shellVars->arg = NULL;
		shellVars->path = NULL;
		if (isatty(STDIN_FILENO) && shellVars->filedesiptor <= 2)
			putString("$ ");
		printErrorChar(EXITT);
		r = getLinee(shellVars);
		if (r != -1)
		{
			InitilizeShellVars(argvM, shellVars);
			builtin_ret = runUserCommand(shellVars);
			if (builtin_ret == -1)
				cmdINEnv(shellVars);
		}
		else if (isatty(STDIN_FILENO) && shellVars->filedesiptor <= 2)
			_putchar('\n');
		clearShellVasrs(shellVars, 0);
	}
	addToHistFile(shellVars);
	clearShellVasrs(shellVars, 1);
	if (!isatty(STDIN_FILENO) && shellVars->filedesiptor <= 2 &&
			shellVars->execStatues)
		exit(shellVars->execStatues);
	if (builtin_ret == -2)
	{
		if (shellVars->errorCode == -1)
			exit(shellVars->execStatues);
		exit(shellVars->errorCode);
	}
	return (builtin_ret);
}

/**
 * runUserCommand - find responsible function
 * @shellVars: struct of variable of custom shell
 * Return: simulate return from document
 */

int runUserCommand(shellVarsStru *shellVars)
{
	int i;
	int func;
	func_node CammandTable[] = {
		{"env", PrintCurrentEnv},
		{"setenv", setVarInEnv},
		{"unsetenv", removeVariableOfEnv},
		{"cd", handleCD},
		{"alias", handleAliasCmd},
		{"history", printHistory},
		{"exit", exitFunc},
		{NULL, NULL}
	};
	func = -1;
	for (i = 0; CammandTable[i].command; i++)
		if (_strcmp(CammandTable[i].command, (shellVars->argv[0])) == 0)
		{
			func = CammandTable[i].func(shellVars);
			shellVars->lCount++;
			break;
		}
	return (func);
}

/**
 * handleFork - handle the fork to keep after excec
 * @shellVars: struct of variable of custom shell
 */

void handleFork(shellVarsStru *shellVars)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shellVars->path, shellVars->argv,
			getEnvironVars(shellVars)) == -1)
		{
			clearShellVasrs(shellVars, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shellVars->execStatues));
		if (WIFEXITED(shellVars->execStatues))
		{
			shellVars->execStatues = WEXITSTATUS(shellVars->execStatues);
			if (shellVars->execStatues == 126)
				showError(shellVars, "Permission denied\n");
		}
	}
}

/**
 * cmdINEnv - find the command in path env
 * @shellVars: struct of variable of custom shell
 */

void cmdINEnv(shellVarsStru *shellVars)
{
	char *path = NULL;
	int i = 0, noDelim = 0;

	shellVars->path = shellVars->argv[0];
	if (shellVars->isNonVide == 1)
	{
		shellVars->isNonVide = 0;
		shellVars->lCount++;
	}
	for (; shellVars->arg[i]; i++)
		if (!isEqualsOne(shellVars->arg[i], " \t\n"))
			noDelim++;
	if (!noDelim)
		return;
	path = getPath(getVariableOfEnv(shellVars, "PATH="), shellVars->argv[0]);
	if (path)
	{
		shellVars->path = path;
		handleFork(shellVars);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && shellVars->filedesiptor <= 2) ||
			getVariableOfEnv(shellVars, "PATH=")
			|| shellVars->argv[0][0] == '/') && isCommand(shellVars->argv[0]))
			handleFork(shellVars);
		else if (*(shellVars->arg) != '\n')
		{
			shellVars->execStatues = 127;
			showError(shellVars, "not found\n");
		}
	}

}

