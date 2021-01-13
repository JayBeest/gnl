/*
** 1. Compile with -D MALLOC_DEBUG to make malloc fail
** 2. set M_ERR to the value of which malloc you want to fail (1 = first malloc fails)
*/
#ifdef MALLOC_DEBUG
# include <stdlib.h>
#ifndef M_ERR
# define M_ERR 10
#endif
int m_cnt = 1;
# define malloc(x) ((m_cnt++ % M_ERR) == 0 ? ((void*)0) : malloc(x))
#endif

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!(dest) && !(src))
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstr = (char *)malloc(len_s1 + len_s2 + 1);
	if (newstr)
	{
		ft_memcpy(newstr, s1, len_s1);
		ft_memcpy(&newstr[len_s1], s2, len_s2 + 1);
		return (newstr);
	}
	return (NULL);
}
