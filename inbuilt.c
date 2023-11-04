#include "shell.h"

/**
 * _exiter: shuts the shell
 * @info: Potential Arguments of structure are contained here.
 * Return: it exists with an inputed exit status
 * (0) when info.argv[0] is not equal to "exit"
 */
int _exiter(info_t *info)
{
	int exitor;

	if (info->argv[1])
	{
		exitor = _erri(info->argv[1]);
		if (exitor == -1)
		{
			info->status = 2;
			errprnt(info, "Illegal number: ");
			_laput(info->argv[1]);
			laputchar('\n');
			return (1);
		}
		info->err_num = erri(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cdr: this changes the current directory of the process
 * @info: potential arguments of the structure are contained here
 *
 * Return: 0 Always
 */
int _cdr(info_t *info)
{
	char *s, *fldr, buffer[1024];
	int cdr_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: failed to cwd\n");
	if (!info->argv[1])
	{
		fldr = _getenv(info, "HOME=");
		if (!fldr)
			chdir_ret = "TODO: failed\n"
				chdir((dir = _getenv(info, "PWD=")) ? fldr : "/");
		else
			cdr_ret = chdir(fldr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cdr_ret = " TODO: got" 
			cdr((fldr = _getenv(info, "OLDPWD=")) ? fldr : "/");
	}
	else
		cdr_ret = cdr(info->argv[1]);
	if (cdr_ret == -1)
	{
		errprnt(info, "can't cd to ");
		_laput(info->argv[1]), _laputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help: this function change the current directory of the process
 * @info: potential arguments of the structure are contained here
 *
 * Return: 0 Always
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Call is fine.. Function not found \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
