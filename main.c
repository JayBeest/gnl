#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    int     fd2;
    int     rv;
    int		rv2;
    char    *line;

    fd = 0;
    fd2 = 0;
	//retry_from_start:
    rv = 1;
    rv2 = 1;
    line = NULL;
    if (argc == 1)
    {
        fd = open("empty", O_RDONLY);
        fd2 = open("empty", O_RDONLY);
    }
    else if (argc == 2)
	{
		if (*argv[1] == '0')
			fd = 0;
		else
			fd = open(argv[1], O_RDONLY);
	}
    else if (argc == 3)
    {
            fd = open(argv[1], O_RDONLY);
            fd2 = open(argv[2], O_RDONLY);
    }
    if (fd == -1 || fd2 == -1)
	{
		printf("fd error -1\n");
		return (0);
	}
	while (1)
	{
		if (rv > 0)
		{
			rv = get_next_line(fd, &line);
			if (rv == -1)
			{
				printf("rv1: -1\n");
				free(line);
				break ;
			}
			printf("rv1: %d,  ->%s|\n", rv, line);
			free(line);
		}
		if (rv == 0)
		{

		}
		if (rv2 > 0)
		{
			rv2 = get_next_line(fd2, &line);
			if (rv2 == -1)
			{
				printf("rv1: -1\n");
				free (line);
				break;
			}
			printf("rv2: %d,  ->%s|\n", rv2, line);
			free(line);
		}
//        while (1)
//		{}

        // if (rv == -1)
		// {
		// 	close(fd);
		// 	goto retry_from_start;
		// }
		if (!rv && !rv2)
			break ;
	}

    close(fd);
	close(fd2);
	//goto retry_from_start;
	while (1)
	{}
    return (0);
}
