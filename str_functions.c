#include "main.h"

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
 *_strcat - appends the src string to the dest string
 *@dest: main String that we append to
 *@src: String to appended to dest
 *Return: a pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{

	int i = 0, dest_index = 0;

	while (dest[i++])
		dest_index++;

	for (i = 0; src[i]; i++)
	{
		dest[dest_index] = src[i];
		dest_index++;
	}
	return (dest);
}

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
