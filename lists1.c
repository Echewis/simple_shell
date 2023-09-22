#include "wem_karl.h"

/**
 * getListLength - This determines the length of linked list
 * @hd: This is a pointer to first node
 * Return:This will return size of list
 */
size_t getListLength(const list_t *hd)
{
	size_t a = 0;

	while (hd)
	{
		hd = hd->next;
		a++;
	}
	return (a);
}

/**
 * **convertListToStringArray - it returns an array of strings ofthe list->str
 * @head: This points to the first node
 * Return: Will return array of strings
 */
char **convertListToStringArray(list_t *head)
{
	list_t *node = head;
	size_t a = getListLength(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(getStrLen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = copyStr(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * printListElements - This will print all elements of a list_t linked list
 * @head: This is a pointer to first node
 * Return: It will return size of list
 */
size_t printListElements(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		putStr(NumberToString(head->num, 10, 0));
		putChar(':');
		putChar(' ');
		putStr(head->str ? head->str : "(nil)");
		putStr("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * *findNodeStartingWith - will return node whose string starts with pre
 * @node: Its a pointer to list head
 * @pre:This ia a string to match
 * @ch: This is the next character after pre to match
 * Return: It will match node or null
 */
list_t *findNodeStartingWith(list_t *node, char *pre, char ch)
{
	char *ph = NULL;

	while (node)
	{
		ph = starts_with(node->str, pre);
		if (ph && ((ch == -1) || (*ph == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - This will get the index of a node
 * @head: This is a pointer to list head
 * @node: This is a pointer to the node
 * Return: It will return index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
