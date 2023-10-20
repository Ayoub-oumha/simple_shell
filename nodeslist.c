#include "main.h"

/**
 * getLengthList - get length of list
 * @h: adresws of header
 * Return: len
 */
size_t getLengthList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listString - list to str
 * @head: adress of header
 * Return: strings
 */

char **listString(list_t *head)
{
	list_t *currentNode = head;
	size_t i, j, len = getLengthList(head);
	char *str, **result;

	if (!head || !len)
		return (NULL);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	for (i = 0; currentNode; currentNode = currentNode->next, i++)
	{
		str = malloc(_strlen(currentNode->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(result[j]);
			free(result);
			return (NULL);
		}

		str = _strcpy(str, currentNode->str);
		result[i] = str;
	}

	result[i] = NULL;

	return (result);
}

/**
 * get_node_index - get index of node
 * @head: adress of header
 * @currentNode: pointer to node
 * Return: index ORC -1
 */

ssize_t get_node_index(list_t *head, list_t *currentNode)
{
	size_t i = 0;

	while (head)
	{
		if (head == currentNode)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * getNodeSta - get node which start with start
 * @head: adress of header
 * @start: start
 * @c: the next character after start
 * Return: match node
 */

list_t *getNodeSta(list_t *head, char *start, char c)
{
	char *temp = NULL;

	while (head)
	{
		temp = findInS(head->str, start);
		if (temp && ((c == -1) || (*temp == c)))
			return (head);
		head = head->next;
	}

	return (NULL);
}

