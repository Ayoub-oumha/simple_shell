#include "main.h"

/**
 * PrintCurrentEnv - print env
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int PrintCurrentEnv(shellVarsStru *shellVars)
{
	const list_t *envir = shellVars->envLisst;

	while (envir)
	{
		putString(envir->str ? envir->str : "(nil)");
		putString("\n");
		envir = envir->next;
	}
	return (0);
}

/**
 * getVariableOfEnv - get value of variable from env
 * @shellVars: struct of variable of custom shell
 * @name: variable name
 * Return: value of variable
 */

char *getVariableOfEnv(shellVarsStru *shellVars, const char *name)
{
	list_t *envLisst = shellVars->envLisst;
	char *envVariable;

	while (envLisst)
	{
		envVariable = findInS(envLisst->str, name);
		if (envVariable && *envVariable)
			return (envVariable);
		envLisst = envLisst->next;
	}
	return (NULL);
}

/**
 * removeVariableOfEnv - delete variable from env
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int removeVariableOfEnv(shellVarsStru *shellVars)
{
	int k = 1;
	list_t *env = shellVars->envLisst;
	size_t i = 0;
	char *findpos;
	char *nameVar;

	if (!env)
		return (0);
	if (shellVars->lenAgrument == 1)
	{
		printError("Too few arguements.\n");
		return (1);
	}
	for (; k <= shellVars->lenAgrument; k++)
	{
		env = shellVars->envLisst;
		nameVar =  shellVars->argv[k];
		if (!nameVar)
			return (0);
		while (env)
		{
			findpos = findInS(env->str, nameVar);
			if (findpos && *findpos == '=')
			{
				env = shellVars->envLisst;
				i = 0;
				shellVars->isEnvChanged =
					delete_nodeint_at_index(&(shellVars->envLisst), i);
				continue;
			}
			env = env->next;
			i++;
		}
	}
	return (0);
}

/**
 * setVarInEnv - add variable ORC edit it in env
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int setVarInEnv(shellVarsStru *shellVars)
{
	if (shellVars->lenAgrument != 3)
	{
		printError("Incorrect number of arguements\n");
		return (1);
	}
	if (setVarsEnvs(shellVars->argv[1], shellVars->argv[2], shellVars))
		return (0);
	return (1);
}

