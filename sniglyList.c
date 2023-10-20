#include "main.h"

/**
 * add_node - adds a new node at the beginning of a list_t list.
 * @head: adress of head node
 * @str: str
 * @num: node index
 * Return: size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - adds a new node at the end of a list_t list.
 * @head: adress of the head node
 * @str: string of new node
 * @n: index
 * Return: address of the new node
 */
list_t *add_node_end(list_t **head, const char *str, int n)
{
	list_t *new, *node;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = strdup(str);
	new->num = n;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new);
}

/**
 * delete_nodeint_at_index - deletes the node at index
 * @head: adress of the head node
 * @index: index
 * Return: 1 if success
 */

int delete_nodeint_at_index(list_t **head, unsigned int index)
{
	list_t *temp, *toDelete;
	unsigned int i;

	if (head == NULL || *head == NULL)
		return (0);

	if (index == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	temp = *head;
	for (i = 0; i < index - 1 && temp; i++)
	{
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);

	toDelete = temp->next;
	temp->next = toDelete->next;
	free(toDelete);
	return (1);
}

/**
 * tortoiseAndHaret - Tortoise ANDC Hare Algorithm find loop
 * @head: head of list
 * Return: the real len of there is loop, else 0
 */

size_t tortoiseAndHaret(const list_t *head)
{
	const list_t *tortoise, *hare;
	size_t len = 1;

	if (head == NULL || head->next == NULL)
		return (0);
	tortoise = head;
	hare = head;
	while (hare != NULL && hare->next != NULL)
	{
		tortoise = tortoise->next;
		hare = hare->next->next;
		if (tortoise == hare)
			break;
	}
	if (tortoise == hare)
	{
		tortoise = head;
		while (tortoise != hare)
		{
			len++;
			tortoise = tortoise->next;
			hare = hare->next;
		}
		hare = hare->next;
		while (hare != tortoise)
		{
			len++;
			hare = hare->next;
		}
		return (len);
	}
	return (0);
}

/**
 * free_listint_safe - Free (safe version) a listint_t
 * @h: head of list
 * Return: the size of the list that was free’d
 */
void free_listint_safe(list_t **h)
{
	list_t *temp;
	size_t len, i;

	len = tortoiseAndHaret(*h);
	if (!len)
	{
		for (i = 0; *h; i++)
		{
			temp = *h;
			*h = (*h)->next;
			if (temp->str)
				free(temp->str);
			free(temp);
		}
	}
	else
	{
		for (i = 0; i < len; i++)
		{
			temp = *h;
			*h = (*h)->next;
			if (temp->str)
				free(temp->str);
			free(temp);
			ششش
		}
	}
	*h = NULL;
	h = NULL;
}

