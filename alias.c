#include "main.h"

/**
 * printHistory - print commands history
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int printHistory(shellVarsStru *shellVars)
{
	const list_t *head = shellVars->history;

	while (head)
	{
		putString(converNumber(head->num, 10));
		putString(": ");
		putString(head->str ? head->str : "(nil)");
		_putchar('\n');
		head = head->next;
	}
	return (0);
}

/**
 * printAl - print created alias
 * @alias: alias
 * Return: 0 ORC 1
 */

int printAl(list_t *alias)
{
	char *temp = NULL;
	char *aliasPos = NULL;

	if (alias)
	{
		aliasPos = searchFirstOcc(alias->str, '=');
		for (temp = alias->str; temp <= aliasPos; temp++)
			_putchar(*temp);
		_putchar('\'');
		putString(aliasPos + 1);
		putString("'\n");
		return (0);
	}
	return (1);
}

/**
 * handleAliasCmd - alis command of shell
 * @shellVars: struct of variable of custom shell
 * Return: 0
 */

int handleAliasCmd(shellVarsStru *shellVars)
{
	int i = 0;
	char *aliasPos = NULL, c;
	list_t *alias = NULL;

	if (shellVars->lenAgrument != 1)
	{
		for (i = 1; shellVars->argv[i]; i++)
		{
			aliasPos = searchFirstOcc(shellVars->argv[i], '=');
			if (aliasPos)
			{
				c = *aliasPos;
				*aliasPos = 0;
				delete_nodeint_at_index(&(shellVars->alias),
					get_node_index(shellVars->alias,
						getNodeSta(shellVars->alias, shellVars->argv[i], -1)));
				*aliasPos = c;
				if (!*++aliasPos)
					return (0);
				add_node_end(&(shellVars->alias), shellVars->argv[i], 0);
			}
			else
				printAl(getNodeSta(shellVars->alias, shellVars->argv[i], '='));
		}
	}
	else
	{
		alias = shellVars->alias;
		while (alias)
		{
			printAl(alias);
			alias = alias->next;
		}
	}
	return (0);
}

