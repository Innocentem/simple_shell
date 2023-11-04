#include "shell.h"

/**
 * _strlen -  the length of a string is returned
 * @s:  length to check of the string
 *
 * Return:  length of string of integer
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - carries out lexicogarphic comparison of strings.
 * @s1:  first string
 * @s2:  second string
 *
 * Return:  positive if s1 > s2, zero if s1 == s2, negative if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - confirms if  haystack started with needle
 * @haystack: the search string
 * @needle: the find substring
 *
 * Return:  next char address of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat -  two strings are concatenated.
 * @dest:  buffer destination
 * @src: the buffer source
 *
 * Return: points to buffer destination
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
