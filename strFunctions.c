#include "main.h"

/**
* _strncpy - copies a string, including the at most specefic n number
*@dest: the result string ORC the main String
*@src: String that we are copying
*@n: max nummber of byte copied
*Return: a pointer to the resulting string dest
*/

char *_strncpy(char *dest, char *src, int n)
{

	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for ( ; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 *_strncat - append specefic n of character from src to dest
 *@dest: main String that we append to
 *@src: String to appended to dest
 *@n: number of character to append
 *Return: a pointer to the resulting string dest
 */

char *_strncat(char *dest, char *src, int n)
{

	int i = 0, dest_index = 0;

	while (dest[i++])
		dest_index++;

	for (i = 0; src[i] && i < n; i++)
		dest[dest_index++] = src[i];

	return (dest);

}

/**
 **searchFirstOcc - find first occurence of c in s
 *@s: search in
 *@c: search for
 *Return: where founded
 */

char *searchFirstOcc(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * converNumber - converter number
 * @number: number
 * @base: base
 * Return: string
 */
char *converNumber(long int number, int base)
{
	static char *array;
	static char buffer[1024];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = "0123456789";
	ptr = &buffer[1023];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

