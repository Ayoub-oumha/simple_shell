#include "main.h"

/**
 * getShellH - gets history file
 * @shellVars: struct of variable of custom shell
 * Return: string of path history
 */

char *getShellH(shellVarsStru *shellVars)
{
	char *homeDir;
	char *buffer;

	homeDir = getVariableOfEnv(shellVars, "HOME=");
	if (!homeDir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(homeDir) + 10));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, homeDir);
	_strcat(buffer, "/");
	_strcat(buffer, ".AlxshellH");
	return (buffer);
}

/**
 * addToHistFile - create file if don't exist ORC append to it
 * @shellVars: struct of variable of custom shell
 * Return: 1 if success
 */

int addToHistFile(shellVarsStru *shellVars)
{
	ssize_t fd;
	char *executableName = getShellH(shellVars);
	list_t *histNode = NULL;

	if (!executableName)
		return (-1);

	fd = open(executableName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(executableName);
	if (fd == -1)
		return (-1);
	for (histNode = shellVars->history; histNode; histNode = histNode->next)
	{
		writeStringToFd(histNode->str, fd);
		writeToFd('\n', fd);
	}
	writeToFd(EXITT, fd);
	close(fd);
	return (1);
}
/**
 * getEnvironVars - get env in string
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

char **getEnvironVars(shellVarsStru *shellVars)
{
	if (!shellVars->environ || shellVars->isEnvChanged)
	{
		shellVars->isEnvChanged = 0;
		shellVars->environ = listString(shellVars->envLisst);
	}

	return (shellVars->environ);
}

/**
 * setVarsEnvs - new Var Env ORC edit
 * @nameVar: name of variable
 * @valueVar: value of variable
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int setVarsEnvs(char *nameVar, char *valueVar, shellVarsStru *shellVars)
{
	list_t *env;
	char *buffer = NULL, *findpos;

	if (!nameVar || !valueVar)
		return (0);
	buffer = malloc(_strlen(nameVar) + _strlen(valueVar) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, nameVar);
	_strcat(buffer, "=");
	_strcat(buffer, valueVar);
	env = shellVars->envLisst;
	while (env)
	{
		findpos = findInS(env->str, nameVar);
		if (findpos && *findpos == '=')
		{
			shellVars->isEnvChanged = 1;
			free(env->str);
			env->str = buffer;
			return (0);
		}
		env = env->next;
	}
	shellVars->isEnvChanged = 1;
	add_node_end(&(shellVars->envLisst), buffer, 0);
	free(buffer);
	return (0);
}




