#include "shell.h"

/**
 * bfree -  it releases or frees a pointer and the address nulled
 * @ptr: address of a ptr to be freed
 *
 * Return: 1 when freed,  0 if not freed.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
