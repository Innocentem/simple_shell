#include "shell.h"

/**
 * _laput - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void _laput(char *str)
{
	int i = 0;

	if (!str)
	return;
	while (str[i] != '\0')
	{
		laputchar(str[i]);
		i++;
	}
										}

/**
* laputchar - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/

int laputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
		return (1);
}

/**
 * put_a: writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_a(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
		return (1);
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
		return (1);
	}
}

/**
 *  * la_puta: prints an input string
 *   * @str: the string to be printed
 *    * @fd: the filedescriptor to write to.
 *     * Return: the number of chars put
 *      */

int la_puta(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_a(*str++, fd);
	}
	return (i);
}
