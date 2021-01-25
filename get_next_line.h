#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

# include <stdlib.h>

typedef struct  gnl_struc
{
    int     			fd;
    void 				*prev_list;
    int                 bytes_read;
    int                 hasnl;
    char    			*leftover;
	char				*ln_ptr;
	char 				*lo_ptr;
	struct gnl_struc	*next;
}               				gnl_struct;

int     get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
// char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
