#include "../includes/libft.h"

char	*ft_strdup(char *src)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	src_size = ft_strlen(src);
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	while (i < src_size)
	{
		string[i] = src[i];
		i++;
	}
	string[src_size] = '\0';
	return (string);
}
