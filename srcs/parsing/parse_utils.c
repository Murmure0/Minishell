#include "../../includes/minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char	*str_slice(char *src, int start, int stop)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	src_size = stop - start;
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (start < stop)
	{
		string[i] = src[start];
		i++;
		start++;
	}
	string[src_size] = '\0';
	return (string);
}

void	skip_spaces(t_parsing *ps)
{
	while (ps->nodes[ps->i][ps->j] && is_space(ps->nodes[ps->i][ps->j]))
	{
		if (ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
	}
}
