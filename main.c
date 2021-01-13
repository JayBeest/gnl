#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    int     rv;
    char    *line;

    fd = 0;
    rv = 1;
    line = NULL;
	retry_from_start:
    if (argc == 1)
        fd = open("./gnl.txt", O_RDONLY);
    else if (argc == 2)
	{
		if (*argv[1] == '0')
			fd = 0;
		else
			fd = open(argv[1], O_RDONLY);
	}
    if (fd == -1)
	{
		printf("fd error -1\n");
		return (0);
	}
	while (rv != 0)
	{
		rv = get_next_line(fd, &line);
		printf("rv: %d,  ->%s|\n", rv, line);
		free(line);
		// if (rv == -1)
		// {
		// 	close(fd);
		// 	goto retry_from_start;
		// }
	}
    close(fd);
    return (0);
}
