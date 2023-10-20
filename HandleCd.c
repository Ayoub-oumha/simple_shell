#include "main.h"

/**
 * isEqualsOne - is on from check in c
 * @c: char
 * @check: string
 * Return: 1 if in c
 */
int isEqualsOne(char c, char *check)
{
	while (*check)
		if (*check++ == c)
			return (1);
	return (0);
}

/**
 * isInt - is s integer
 * @s: string
 * Return: is integer
 */
int isInt(char *s)
{
	int i = 0;
	unsigned long int inNumber = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			inNumber *= 10;
			inNumber += (s[i] - '0');
			/* if (inNumber > INT_MAX) return (-1);	*/
		}
		else
			return (-1);
	}
	return (inNumber);
}

/**
 * exitFunc - custom exit for simple shell
 * @shellVars: struct of variable of custom shell
 * Return: code
 */

int exitFunc(shellVarsStru *shellVars)
{
	if (shellVars->argv[1])
	{
		if (isInt(shellVars->argv[1]) == -1)
		{
			shellVars->execStatues = 2;
			showError(shellVars, "Illegal number: ");
			printError(shellVars->argv[1]);
			printErrorChar('\n');
			return (1);
		}
		shellVars->errorCode = isInt(shellVars->argv[1]);
		return (-2);
	}
	shellVars->errorCode = -1;
	return (-2);
}

/**
 * handleBACKDIR - handl cd -.
 * @shellVars: struct of variable of custom shell
 */

void handleBACKDIR(shellVarsStru *shellVars)
{
	char buffer[1024], *s;

	s = getcwd(buffer, 1024);
	if (!getVariableOfEnv(shellVars, "BACKDIR="))
	{
		putString(s);
		_putchar('\n');
	}
	putString(getVariableOfEnv(shellVars, "BACKDIR="));
	_putchar('\n');
}

/**
 * handleCD - handle cd command
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int handleCD(shellVarsStru *shellVars)
{
	int toDir;
	char buffer[1024], *s, *dir;

	s = getcwd(buffer, 1024); /*get Current Directory*/
	if (!s)
		putString("TODO: >>getcwd failure emsg here<<\n");
	if (!shellVars->argv[1])
	{
		dir = getVariableOfEnv(shellVars, "HOME=");
		if (!dir)
			toDir =
			chdir((dir = getVariableOfEnv(shellVars, "PWD=")) ? dir : "/");
		else
			toDir = chdir(dir);
	}
	else if (_strcmp(shellVars->argv[1], "-") == 0)
	{
		handleBACKDIR(shellVars);
		if (!getVariableOfEnv(shellVars, "BACKDIR="))
			return (1);
		toDir =
		chdir((dir = getVariableOfEnv(shellVars, "BACKDIR=")) ? dir : "/");
	}
	else
		toDir = chdir(shellVars->argv[1]);
	if (toDir == -1)
	{
		showError(shellVars, "can't cd to ");
		printError(shellVars->argv[1]);
		printErrorChar('\n');
	}
	else
	{
		setVarsEnvs("BACKDIR", getVariableOfEnv(shellVars, "PWD="), shellVars);
		setVarsEnvs("PWD", getcwd(buffer, 1024), shellVars);
	}
	return (0);
}

