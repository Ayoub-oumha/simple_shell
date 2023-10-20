#include "main.h"

/**
* _strcpy - Copy string
*@dest: destination
*@src: source
*Return: dest
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

/**
* _strdup - returns a pointer to a newly allocated space in memory
*which contains a copy of the string given as a parameter
*@str:String to copy
*Return: NULL if error
*pointer if it success
*/

char *_strdup(const char *str)
{
	char *duplicate;
	int i = 0, size = 0;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i]; i++)
		size++;
	duplicate = malloc(sizeof(char) * (size + 1));

	if (duplicate == NULL)
		return (NULL);

	for (i = 0; str[i]; i++)
	{
		duplicate[i] = str[i];
	}

	duplicate[size] = '\0';

	return (duplicate);

}

/**
 *putString - print string
 *@s: string
 */

void putString(char *s)
{
	if (!s)
		return;
	while (*s)
	{
		_putchar(*s);
		s++;
	}
}

/**
 * _putchar - writes char to stdout
 * @c: The char
 * Return: 1 of success
 */

int _putchar(char c)
{
	static int c_len;
	static char buffer[OUTPUT_BUF_SIZE];

	if (c == EXITT || c_len >= OUTPUT_BUF_SIZE)
	{
		write(1, buffer, c_len);
		c_len = 0;
	}
	if (c != EXITT)
	{
		buffer[c_len] = c;
		c_len++;
	}
	return (1);
}

