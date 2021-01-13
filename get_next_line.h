#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32 
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

typedef struct  gnl_struc
{
    int     			fd;
    char    			*leftover;
	char				*lo_ptr;
	struct gnl_struc	*next;
}               				gnl_struct;

int     get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
// char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
