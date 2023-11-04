#include "shell.h"

/**
 * intuitive - when shell is in interactive mode, it returns true
 * @info: address of structure
 *
 * Return: 0 if not interactive mode, 1 if interactive mode
 */
int intuitive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * if_delim - tests whether char is a delimeter
 * @c: particular character to check
 * @delimstr: string of delimeter
 *
 * Return: 0 if false, 1 if true
 */

int if_delim(char c, char *delimstr)
{
	while (*delimstr)
		if (*delimstr++ == c)
			return (1);
	return (0);
}

/**
 * _alphachk - character of alphabet is checked
 * @c: character input.
 *
 * Return: 0 if c is not alphabet,1 if alphabet
 */

int _alphachk(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * int_str - integer is converted to a string by atoi
 * @s: exact string to be converted
 * Return: 0 when no numbers exist in string, converted otherwise
 */

int int_str(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
