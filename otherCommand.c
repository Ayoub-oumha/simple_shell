#include "main.h"
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

/**
*_memset - fills memory with a constant byte
*@s: pointer of memory area
*@b: constant byte.
*@n: n bytes of the memory
*Return: returns new value of target
*/

char *_memset(char *s, char b, unsigned int n)
{
	while (n)
	{
		s[n - 1] = b;
		n--;
	}
	return (s);
}

/**
* _realloc -  reallocates a memory block using malloc ANDC free
* @ptr: pointer to the memory previously allocated
* @old_size: size of ptr
* @new_size: size of the new memory block
* Return: pointer to the result
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int i;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	else if (new_size == old_size)
		return (ptr);

	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp_block = malloc(new_size);
		if (temp_block == NULL)
			return (NULL);
		for (i = 0; i < min(old_size, new_size); i++)
		*((char *)temp_block + i) = *((char *) ptr + i);
		free(ptr);
		return (temp_block);
	}
}


/**
 * setCmdType - set type of cmd in struct
 * @buffer: buffer
 * @currentPos: address curen pos in buff
 * @ShVar: struct of varialbe of simple shell
 * Return: 1
 */

int setCmdType(char *buffer, size_t *currentPos, shellVarsStru *ShVar)
{
	size_t i = *currentPos;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		ShVar->CMDORAND = ORC;
		buffer[i] = 0;
		i++;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		ShVar->CMDORAND = ANDC;
		buffer[i] = 0;
		i++;
	}
	else if (buffer[i] == ';')
	{
		ShVar->CMDORAND = CHNN;
		buffer[i] = 0;

	}
	else
		return (0);
	*currentPos = i;
	return (1);
}

/**
 * setAliasVar - set value of var in alias
 * @ShVar: struct of varialbe of simple shell
 * Return: 1
 */

int setAliasVar(shellVarsStru *ShVar)
{
	list_t *envVariable;
	int i = 0;

	for (i = 0; ShVar->argv[i]; i++)
	{
		if (!ShVar->argv[i][1] || ShVar->argv[i][0] != '$')
			continue;
		if (!_strcmp(ShVar->argv[i], "$$"))
		{
			free(ShVar->argv[i]);
			ShVar->argv[i] = _strdup(converNumber(getpid(), 10));
			continue;
		}
		if (!_strcmp(ShVar->argv[i], "$?"))
		{
			free(ShVar->argv[i]);
			ShVar->argv[i] = _strdup(converNumber(ShVar->execStatues, 10));
			continue;
		}
		envVariable = getNodeSta(ShVar->envLisst, &ShVar->argv[i][1], '=');
		if (envVariable)
		{
			free(ShVar->argv[i]);
			ShVar->argv[i] = _strdup(searchFirstOcc(envVariable->str, '=') + 1);
			continue;
		}
		free(ShVar->argv[i]);
		ShVar->argv[i] = _strdup("");
	}
	return (0);
}

