#include "shell.h"

/**
 * _memset: a constnt byte is filled by memory
 * @s: points the ptr to the memory area
 * @b: *s is filled with the byte
 * @n: no. of bytes to be filled.
 *
 * Return: (s) as a pointer to the s of memory area
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree: str of strngs is freed
 * @pp: strng of strngs.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc: block of memory is re'llctd.
 * @ptr: points to former block of malloc
 * @old_size - size of byte of former block
 * @new_size: - size of byte of new block
 *
 * Return: points to oldblk.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
