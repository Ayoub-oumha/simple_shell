#include "main.h"

/**
	*_strcmp - function that compares two strings.
	*@s1: first string
	*@s2: second string
	*Return:
	*zero if s1 == s2
	*else return to result of s1 -s2
*/

int _strcmp(char *s1, char *s2)
{

	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
return (0);
}

/**
* _atoi - convert a string to an integer.
* @s: the string
* Return: the string in int
*/

int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
			num = num * 10 + (*s - '0');
		else if (num > 0)
			break;
		s++;
	}
	return (num * sign);
}


/**
 * _itos - int to string
 * @number: number
 * Return: string
*/

char *_itos(int number)
{
	int isNegative = 0;
	int len = 0;
	int pos = number;
	int i = 0;
	static char s[100];

	if (number < 0)
	{
		isNegative = 1;
		pos = -pos;
		len++;
	}
	do {
		len++;
		pos /= 10;
	} while (pos);
	if (s != NULL)
	{
		pos = number;
		i = len - 1;
		if (isNegative)
		{
			s[0] = '-';
			pos = -number;
		}
		do {
			s[i] = '0' + (pos % 10);
			pos /= 10;
			i--;
		} while (pos);
		s[len] = '\0';
	}
	return (s);
}
