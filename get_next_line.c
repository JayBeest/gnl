/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 11:33:13 by jcorneli      #+#    #+#                 */
/*   Updated: 2021/01/31 16:20:05 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#include <stdio.h>

static int			freedom(gnl_struct **gnls, int rv)
{
	gnl_struct			*cur_list;
	gnl_struct			*prev_list;
	gnl_struct			*next_list;

	cur_list = *gnls;
	prev_list = cur_list->prev_list;
	next_list = cur_list->next;
	if (rv < 1)
	{
		free(cur_list->leftover);
		if (prev_list == NULL)
		{
			*(cur_list->gnlstatic) = next_list;
			if (next_list)
				next_list->prev_list = NULL;
		}
		else
			prev_list->next = cur_list->next;
		free(cur_list);
		return (rv);
	}
	return (1);
}

static gnl_struct	*new_fd(int fd, gnl_struct *prev_list,\
					gnl_struct **gnlstatic)
{
	gnl_struct			*new;

	new = (gnl_struct *)malloc(sizeof(gnl_struct));
	if (new)
	{
		new->fd = fd;
		new->prev_list = prev_list;
		new->gnlstatic = gnlstatic;
		new->leftover = ft_strjoin("", "");
		if (!new->leftover)
		{
			free(new);
			return (NULL);
		}
		new->ln_ptr = NULL;
		new->next = NULL;
		new->bytes_read = 1;
		new->hasnl = 0;
		return (new);
	}
	return (NULL);
}

static gnl_struct	*get_fd(gnl_struct **gnlstatic, int fd)
{
	gnl_struct			*node;

	node = *gnlstatic;
	if (!node)
		return (NULL);
	while (node)
	{
		if (node->fd == fd)
			return (node);
		if (node->next == NULL)
		{
			node->next = new_fd(fd, node, gnlstatic);
			return (node->next);
		}
		node = node->next;
	}
	return (NULL);
}

static int			check_nl(char *buff, char **ln, gnl_struct *gnls)
{
	int					i;

	i = 0;
	gnls->ln_ptr = *ln;
	gnls->lo_ptr = gnls->leftover;
	while (buff[i])
	{
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			gnls->leftover = ft_strjoin("", &buff[i + 1]);
			if (!gnls->leftover)
				return (freedom(&gnls, -1));
			gnls->hasnl = 1;
			break ;
		}
		i++;
	}
	*ln = ft_strjoin(*ln, buff);
	if (gnls->hasnl)
		free(gnls->lo_ptr);
	free(gnls->ln_ptr);
	if (*ln)
		return (gnls->hasnl);
	return (freedom(&gnls, -1));
}

int					get_next_line(int fd, char **line)
{
	char				buffer[BUFFER_SIZE + 1];
	gnl_struct			*gnls;
	static gnl_struct	*gnlstatic;

	if (!gnlstatic)
		gnlstatic = new_fd(fd, NULL, &gnlstatic);
	gnls = get_fd(&gnlstatic, fd);
	if (!gnls)
		return (-1);
	*line = ft_strjoin("", "");
	if (!*line)
		return (freedom(&gnls, -1));
	if (check_nl(gnls->leftover, line, gnls) == -1)
		return (-1);
	while (!gnls->hasnl)
	{
		gnls->bytes_read = read(gnls->fd, buffer, BUFFER_SIZE);
		buffer[gnls->bytes_read] = '\0';
		if (gnls->bytes_read <= 0)
			break ;
		if (check_nl(buffer, line, gnls) == -1)
			return (-1);
	}
	gnls->hasnl = 0;
	return (freedom(&gnls, gnls->bytes_read));
}
