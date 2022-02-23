#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*buffer;

	buffer = (char *)s;
	i = 0;
	while (i < n)
	{
		buffer[i] = '\0';
		i++;
	}
	s = (void *)buffer;
}
