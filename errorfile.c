#include "shell.h"

/**
 * erri: converts a string to an integer
 * @s: the to be converted string
 * Return: 0 when no numbers are in string, converted number otherwise
 *        on error -1
 */
int erri(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * errprnt: an error message is printed
 * @info: return info structure & the parameter
 * @estr: the exact string containing specified error type
 * Return: 0 when no nos in string, converted number otherwise
 *         on error -1
 */
void errprnt(info_t *info, char *estr)
{
	_laput(info->fname);
	_laput(": ");
	dprint(info->line_count, STDERR_FILENO);
	_laput(": ");
	_laput(info->argv[0]);
	_laput(": ");
	_laput(estr);
}

/**
 * dprint: a decimal integer of base 10 is printed
 * @input: input
 * @fd: writes the exact filedescriptor
 * Return: no of printed characters
 */
int dprint(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = laputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * fn_cnvt - function converter
 * @num: numbers
 * @base: base
 * @flags:  flags of argument
 * Return: string
 */

char *fn_cnvt(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _comrmv - first instance of '#'is replaced with '\0' by function
 * @buf: the address of the string to modify
 *
 * Return: 0 Always;
 */
void _comrmv(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
