/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 11:33:13 by jcorneli      #+#    #+#                 */
/*   Updated: 2020/12/21 15:45:57 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#include <stdio.h>

static int	check_nl(char *buffer, char **line, char **leftover)
{
	int		i;
	int		isnl;
	char	*l_ptr;

	i = 0;
	isnl = 0;
	l_ptr = *line;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			*leftover = ft_strjoin("", &buffer[i + 1]);
			if (!*leftover)
				return (-1);
			isnl = 1;
			break ;
		}
		i++;
	}
	*line = ft_strjoin(*line, buffer);
	if (*line)
		return (isnl);
	return (-1);
}

static gnl_struct	*check_fd(gnl_struct *gnls, int fd)
{
	gnl_struct	*new;
// eerst checken op fd -<
	new = NULL;
	if (!gnls)
	{
		new = (gnl_struct *)malloc(sizeof(gnl_struct));
		if (new)
		{
			new->fd = fd;
			new->leftover = ft_strjoin("", "");
			if (!new->leftover)
				return (NULL); // <-----free?
			new->lo_ptr = NULL;
			new->next = NULL;
			return (new);
		}
		return (NULL);
	}

	return (NULL);
}

int			get_next_line(int fd, char **line)
{
	// static char	*leftover;
	char				buffer[BUFFER_SIZE + 1];
	int					bytes_read;
	int					isnl;
	static gnl_struct	*gnls;

	gnls = check_fd(gnls, fd);
	
	isnl = 0;
	bytes_read = 1;
	*line = ft_strjoin("", "");
	if (!*line)
		return (-1);
	// if (!leftover)
	// 	leftover = "";
	// else
		isnl = check_nl(gnls->leftover, line, &gnls->leftover);
	while (isnl == 0)
	{
		bytes_read = read(gnls->fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		isnl = check_nl(buffer, line, &gnls->leftover);
		if (!*line)
			return (-1);
	}
	return (bytes_read > 0);
}
