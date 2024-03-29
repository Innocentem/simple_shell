#include "shell.h"

/**
 * get_history_file: to get the history file
 * @info - parameter of structure.
 * Return: allocated string containg history file.
 */

char *get_history_file(info_t *info)
{
    char *buf;

info->path = getenv("HOME");
    if (!info->path)
        return (NULL);

    buf = malloc(sizeof(char) * (_strlen(info->path) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, info->path);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}
/**
 * write_history: to create a file / append to an existing file
 * @info: struct parameter.
 *
 * Return: success 1, failure -1.
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;
    ssize_t newline_written;
    (void)newline_written;

    if (!filename) {
        return -1;
    }

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    for (node = info->history; node; node = node->next)
    {
        if (node->str != NULL) {
            newline_written = write(fd, node->str, strlen(node->str));
            write(fd, "\n", 1);
        }
    }

    write(fd, BUF_FLUSH, sizeof(BUF_FLUSH));

    close(fd);

    return 1;
}
                
/**
 * read_history: to read history
 * @info - struct parameter.
 *
 * Return: count if success, 0 for failure
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list: it adds entry to a history linked list
 * @info - Struct info
 * @buf: buffr
 * @linecount: history linecount..
 * Return: 0.
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_node_endplus(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history:  renumbering the history linked list after changes.
 * @info: Struct info
 *
 * Return: latest historycount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
