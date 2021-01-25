/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 11:33:13 by jcorneli      #+#    #+#                 */
/*   Updated: 2021/01/22 13:41:27 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#include <stdio.h>

static int 			freedom(gnl_struct **gnls, int rv)
{
	gnl_struct			*cur_list;
	gnl_struct			*prev_list;

	cur_list = *gnls;
	prev_list = cur_list->prev_list;

	if (rv < 1)
	{
		if (cur_list->leftover)
			free(cur_list->leftover);
		if (cur_list->prev_list == NULL)
			gnls = &cur_list->next;
		else
			prev_list->next = cur_list->next;
		free(cur_list);
		return (rv);
	}
	return (1);
}

static gnl_struct	*new_fd(int fd, gnl_struct *last_list)
{
	gnl_struct			*new;

	new = (gnl_struct *)malloc(sizeof(gnl_struct));
	if (new)
	{
		new->fd = fd;
		new->prev_list = last_list;
		new->leftover = ft_strjoin("", "");
		if (!new->leftover)
		{
			free(new);
			return (NULL);//<-----free!
		}
		new->ln_ptr = NULL;
		new->next = NULL;
		new->bytes_read = 1;
		new->hasnl = 0;
		return (new);
	}
	return (NULL); //<-----free?
}

static gnl_struct	*get_fd(gnl_struct *gnls, int fd)
{
	gnl_struct			*node;

	node = gnls;
	if (!node)
		return (new_fd(fd, NULL));
	while (node)
	{
		if (node->fd == fd)
			return (node);
		if (node->next == NULL)
		{
			node->next = new_fd(fd, node);
			return (node->next);
		}
		node = node->next;
	}
	return (NULL);//<--- ??
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
			gnls->leftover = ft_strjoin("", &buff[i + 1]); //<--- free old *lo??
			free(gnls->lo_ptr);
			if (!gnls->leftover)
				return (freedom(&gnls, -1));
			gnls->hasnl = 1;
			break ;
		}
		i++;
	}
	*ln = ft_strjoin(*ln, buff);
	free(gnls->ln_ptr);// <--- free in free-function?
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
		gnlstatic = new_fd(fd, NULL);
	gnls = get_fd(gnlstatic, fd);
	if (!gnls)
		return (-1);
	*line = ft_strjoin("", "");
	if (!*line)
		return (freedom(&gnls, -1));//<-- free leftover!
	check_nl(gnls->leftover, line, gnls);
	while (!gnls->hasnl)
	{
		gnls->bytes_read = read(gnls->fd, buffer, BUFFER_SIZE);
		if (gnls->bytes_read <= 0)
			break ;
		buffer[gnls->bytes_read] = '\0';
		check_nl(buffer, line, gnls);
		if (!*line)
			return (freedom(&gnls, -1));
	}
	gnls->hasnl = 0;
	return (freedom(&gnls, gnls->bytes_read)); //<--if bytes read 0 free leftover
}
