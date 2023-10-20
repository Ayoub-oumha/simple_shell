#include "main.h"

/**
 * readInput - read input for custem get line
 * @buffer: buffer
 * @i: sizze
 * @shellVars: struct of variable of custom shell
 * Return: s_line
 */
ssize_t readInput(char *buffer, size_t *i, shellVarsStru *shellVars)
{
	int s_line = 0;

	if (*i)
		return (0);
	s_line = read(shellVars->filedesiptor, buffer, 1024);
	if (s_line > -1)
		*i = s_line;

	return (s_line);
}

/**
 * getLIneCustom - get from stdin simulate to getLine
 * @c_buffer: current in buffer
 * @sizze: length
 * @shellVars: struct of variable of custom shell
 * Return: s of line
 */

int getLIneCustom(char **c_buffer, size_t *sizze, shellVarsStru *shellVars)
{
	static char buffer[1024];
	static size_t i, len;
	size_t k;
	ssize_t s_line = 0, s = 0;
	char *currentPosChar = NULL, *new_p = NULL, *c;

	currentPosChar = *c_buffer;
	if (currentPosChar && sizze)
		s = *sizze;
	if (i == len)
		i = len = 0;
	s_line = readInput(buffer, &len, shellVars);
	if (s_line == -1 || (s_line == 0 && len == 0))
		return (-1);
	c = searchFirstOcc(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(currentPosChar, s, s ? s + k : k + 1);
	if (!new_p)
		return (currentPosChar ? free(currentPosChar), -1 : -1);
	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);
	s += k - i;
	i = k;
	currentPosChar = new_p;
	if (sizze)
		*sizze = s;
	*c_buffer = currentPosChar;
	return (s);
}

/**
 * newLineCmd - block unusual go to new liine
 * @sign: signal num
 */

void newLineCmd(int sign)
{
	(void) sign;
	putString("\n$ ");
	_putchar(EXITT);
}

/**
 * getLineee - continued function of get line
 * @shellVars: struct of variable of custom shell
 * @buffer: adress to buf
 * @len: len of buff
 * Return: number readed bytes
 */

ssize_t getLineee(char **buffer, size_t *len, shellVarsStru *shellVars)
{
	int i = 0;
	ssize_t s_line = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, newLineCmd);
		s_line = getLIneCustom(buffer, &len_p, shellVars);
		if (s_line > 0)
		{
			shellVars->isNonVide = 1;
			if ((*buffer)[s_line - 1] == '\n')
			{
				(*buffer)[s_line - 1] = '\0';
				s_line--;
			}
			for (i = 0; (*buffer)[i] != '\0'; i++)
				if ((!i || (*buffer)[i - 1] == ' ') && (*buffer)[i] == '#')
				{
					(*buffer)[i] = '\0';
					break;
				}
			HlistBuild(*buffer, shellVars->historyNLines++, shellVars);
			/*may change it*/
		}
	}

	return (s_line);
}

/**
 * getLinee - get line from input
 * @shellVars: struct of variable of custom shell
 * Return: number readed bytes
 */

ssize_t getLinee(shellVarsStru *shellVars)
{
	static size_t i, i_current, len;
	size_t siz;
	ssize_t s_line = 0;
	static char *buffer;
	char *currentPosChar;
	char **buf_p = &(shellVars->arg);

	_putchar(EXITT);
	s_line = getLineee(&buffer, &len, shellVars);
	if (s_line == -1)
		return (-1);
	if (len)
	{
		i_current = i;
		currentPosChar = buffer + i;
		siz = i_current;
		if ((shellVars->CMDORAND == ANDC && shellVars->execStatues) ||
			(shellVars->CMDORAND == ORC && !shellVars->execStatues))
		{
			buffer[i] = 0;
			siz = len;
		}
		i_current = siz;
		while (i_current++ < len)
			if (setCmdType(buffer, &i_current, shellVars))
				break;
		i = i_current + 1;
		if (i >= len)
		{
			i = len = 0;
			shellVars->CMDORAND = NORM;
		}
		*buf_p = currentPosChar;
		return (_strlen(currentPosChar));
	}
	*buf_p = buffer;

	return (s_line);
}

