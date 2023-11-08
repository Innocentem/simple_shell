#include "shell.h"

/**
 **_strncpy -  a string copier
 *@dest: the string to be copied to a destination
 *@src: source string
 *@n: the no of characters to be copied
 *Return: the string concatenation
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat -  two strings concatenation
 *@dest:  first string
 *@src:  second string
 *@n: the no of bytes to be used maximally
 *Return:  concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr: char in a string location
 *@s - parsed str
 *@c - character to be searched
 *Return: (s).
 */

char *str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
