#include "shell.h"

/**
 * main: checks if my shell is called
 * @ac - arg count
 * @av - arg vectr.
 *
 * Return: 1 on error, 0 on success
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_laput(av[0]);
				_laput(": 0: failure to open ");
				_laput(av[1]);
				laputchar('\n');
				laputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populate_envlist(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
