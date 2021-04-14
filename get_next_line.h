/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 18:30:03 by jcorneli      #+#    #+#                 */
/*   Updated: 2021/01/31 18:30:21 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>

typedef struct s_gnl
{
	int					fd;
	int					bytes_read;
	int					hasnl;
	char				*leftover;
	char				*ln_ptr;
	char				*lo_ptr;
	struct s_gnl		**gnlstatic;
	struct s_gnl		*prev_list;
	struct s_gnl		*next;
}				t_gnl;

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
