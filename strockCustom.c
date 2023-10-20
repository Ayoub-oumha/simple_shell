#include "main.h"

/**
 *_strlen -  function that returns the length of a string.
 * @s: string value
 *Return: returns the length of a string.
 */

int _strlen(char *s)
{
int i;

for (i = 0; s[i] != '\0'; i++)
{
}

return (i);
}

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
 * findInS - checks if toFind starts with s
 * @s: string
 * @toFind: the substring to find in s
 * Return: address of next char after to find
 */

char *findInS(const char *s, const char *toFind)
{
	while (*toFind)
	{
		if (*toFind != *s)
			return (NULL);
		toFind++;
		s++;
	}
	return ((char *)s);
}

/**
 * _strcat - simulate strcat
 * @dest: destination
 * @src: source
 * Return: adress to result
 */

char *_strcat(char *dest, char *src)
{
	char *dupli = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (dupli);
}

/**
 * **strokCustom - simulate to stork()
 * @str: string
 * @d: splitter
 * Return: array of result
 */

char **strokCustom(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isEqualsOne(str[i], d) && (isEqualsOne(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (isEqualsOne(str[i], d))
			i++;
		k = 0;
		while (!isEqualsOne(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

